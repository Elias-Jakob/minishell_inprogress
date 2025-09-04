#include "../../includes/minishell.h"

static t_token	*get_current_token(t_list *token_list);
static t_cmd	*create_new_command(t_token *token);
static t_redirs	*init_redirection(void);
static int	handle_redirection(t_cmd **current_cmd, t_list **token_node);
static int	handle_pipe(t_cmd **current_cmd);
static int	count_argv_size(char **argv);
static int	add_argv_to_command(t_cmd *cmd, t_token *token);
static int	is_redirection_token(t_token *token);
static t_token	*get_next_token(t_list *token_list);

int parser(t_list *token_list, t_cmd **cmd_head)
{
	t_cmd	*current_cmd;
	t_list	*current_token_node;
	t_token	*token;
	t_cmd	*new_cmd;

	*cmd_head = NULL;
	current_cmd = NULL;
	current_token_node = token_list;
	while (current_token_node)
	{
		token = get_current_token(current_token_node);
		if (token->type == TK_WORD && !current_cmd)
		{
			new_cmd = create_new_command(token);
			if (!*cmd_head)
				*cmd_head = new_cmd;
			else
			{
				t_cmd *last = *cmd_head;
				while (last->next)
					last = last->next;
				last->next = new_cmd;
			}
			printf("Token val: %s\n", token->value);
			current_cmd = new_cmd;
		}
		else if ((token->type == TK_WORD || token->type == TK_DOUBLE_QUOTE || token->type == TK_SINGLE_QUOTE) && current_cmd)
		{
			printf("Add argv\n");
			add_argv_to_command(current_cmd, token);
		}
		else if (token->type == TK_PIPE)
		{
			printf("Handling pipe\n");
			handle_pipe(&current_cmd);
		}
		else if (is_redirection_token(token))
		{
			if (handle_redirection(&current_cmd, &current_token_node) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		current_token_node = current_token_node->next;
	}
	return (EXIT_SUCCESS);
}

//------------------------- HEREDOC START -------------------------//
static char	*generate_heredoc_filename(void);
static int	create_heredoc_file(char *delimiter, char **tmp_file_path);
static int	handle_heredoc(t_cmd **current_cmd, t_token *delimiter_token);

static void	cleanup_heredoc(t_redirs *redirs)
{
	if (redirs && redirs->heredoc_content)
	{
		if (unlink(redirs->heredoc_content) == -1)
			perror("minishell: unlink heredoc");
		free(redirs->heredoc_content);
		redirs->heredoc_content = NULL;
	}
}

// static void	free_redirection(t_redirs *redirs)
// {
// 	if (redirs)
// 	{
// 		free(redirs->infile_name);
// 		free(redirs->outfile_name);
// 		free(redirs->heredoc_delimiter);
// 		cleanup_heredoc(redirs);
// 		free(redirs);
// 	}
// }

static int	handle_heredoc(t_cmd **current_cmd, t_token *delimiter_token)
{
	char	*tmp_file_path;

	if (!*current_cmd)
	{
		*current_cmd = create_new_command(NULL);
		if (!*current_cmd)
			return (EXIT_FAILURE);
	}
	if (!(*current_cmd)->redirs)
	{
		(*current_cmd)->redirs = init_redirection();
		if (!(*current_cmd)->redirs)
			return (EXIT_FAILURE);
	}
	(*current_cmd)->redirs->heredoc_delimiter = ft_strdup(delimiter_token->value);
	if (create_heredoc_file(delimiter_token->value, &tmp_file_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	(*current_cmd)->redirs->in_type = RD_HEREDOC;
	(*current_cmd)->redirs->heredoc_content = tmp_file_path;
	return (EXIT_SUCCESS);
}

static int	create_heredoc_file(char *delimiter, char **tmp_file_path)
{
	int		fd;
	char	*line;
	char	*filename;

	filename = generate_heredoc_filename();
	if (!filename)
		return (EXIT_FAILURE);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("minishell: heredoc");
		free(filename);
		return (EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
			break;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	*tmp_file_path = filename;
	return (EXIT_SUCCESS);
}

static char	*generate_heredoc_filename(void)
{
	static int	heredoc_counter = 0;
	char		*filename;
	char		*counter_str;
	char		*tmp_path;

	counter_str = ft_itoa(heredoc_counter++);
	if (!counter_str)
		return (NULL);
	tmp_path = ft_strjoin("_heredoc_", counter_str);
	free(counter_str);
	if (!tmp_path)
		return (NULL);
	filename = ft_strjoin("/tmp/", tmp_path);
	free(tmp_path);
	return (filename);
}

//-------------------------- HEREDOC END --------------------------//

static int	is_token_builtin(t_token *token)
{
	if (token == NULL || token->value == NULL)
		return (EXIT_FAILURE);
	if (ft_strncmp(token->value, "echo", 4) == 0)
		return (EXIT_SUCCESS);
	if (ft_strncmp(token->value, "cd", 2) == 0)
		return (EXIT_SUCCESS);
	if (ft_strncmp(token->value, "pwd", 3) == 0)
		return (EXIT_SUCCESS);
	if (ft_strncmp(token->value, "export", 6) == 0)
		return (EXIT_SUCCESS);
	if (ft_strncmp(token->value, "unset", 5) == 0)
		return (EXIT_SUCCESS);
	if (ft_strncmp(token->value, "env", 3) == 0)
		return (EXIT_SUCCESS);
	if (ft_strncmp(token->value, "exit", 4) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static t_cmd	*create_new_command(t_token *token)
{
	t_cmd	*new_command;

	new_command = malloc(sizeof(t_cmd));
	if (!new_command)
		return (NULL);
	new_command->argv = NULL;
	new_command->redirs = NULL;
	new_command->pid = 0;
	new_command->is_builtin = 0;
	if (token && is_token_builtin(token) == EXIT_SUCCESS)
		new_command->is_builtin = 1;
	new_command->exit_status = 0;
	new_command->next = NULL;
	if (token)
	{
		new_command->argv = malloc(sizeof(char *) * 2);
		if (!new_command->argv)
		{
			free(new_command);
			return (NULL);
		}
		new_command->argv[0] = ft_strdup(token->value);
		if (!new_command->argv[0])
		{
			free(new_command->argv);
			free(new_command);
			return (NULL);
		}
		new_command->argv[1] = NULL;
	}
	return (new_command);
}

static int	add_argv_to_command(t_cmd *cmd, t_token *token)
{
	int		count;
	char	**new_argv;

	if (cmd == NULL || token == NULL)
		return (EXIT_FAILURE);
	count = count_argv_size(cmd->argv);
	new_argv = realloc(cmd->argv, sizeof(char *) * (count + 2));
	if (!new_argv)
		return (EXIT_FAILURE);
	cmd->argv = new_argv;
	cmd->argv[count] = ft_strdup(token->value);
	if (!cmd->argv[count])
		return (EXIT_FAILURE);
	cmd->argv[count + 1] = NULL;
	return (EXIT_SUCCESS);
}

static int	handle_redirection(t_cmd **current_cmd, t_list **token_node)
{
	t_token	*redir_token;
	t_token	*file_token;

	redir_token = get_current_token(*token_node);
	file_token = get_next_token(*token_node);
	if (!file_token)
		return (EXIT_FAILURE);
	if (!*current_cmd)
	{
		*current_cmd = create_new_command(NULL);
		if (!*current_cmd)
			return (EXIT_FAILURE);
	}
	if (!(*current_cmd)->redirs)
	{
		(*current_cmd)->redirs = init_redirection();
		if (!(*current_cmd)->redirs)
			return (EXIT_FAILURE);
	}
	if (redir_token->type == TK_REDIRECT_IN)
	{
		(*current_cmd)->redirs->in_type = RD_FILE;
		(*current_cmd)->redirs->infile_name = ft_strdup(file_token->value);
	}
	else if (redir_token->type == TK_REDIRECT_OUT)
	{
		(*current_cmd)->redirs->out_type = RD_FILE;
		(*current_cmd)->redirs->outfile_name = ft_strdup(file_token->value);
	}
	else if (redir_token->type == TK_APPEND_OUT)
	{
		(*current_cmd)->redirs->out_type = RD_APPEND_OUT;
		(*current_cmd)->redirs->outfile_name = ft_strdup(file_token->value);
		(*current_cmd)->redirs->append_mode = 1;
	}
	else if (redir_token->type == TK_HEREDOC)
	{
		if (handle_heredoc(current_cmd, file_token) == EXIT_FAILURE)
		{
			if (*current_cmd && (*current_cmd)->redirs)
				cleanup_heredoc((*current_cmd)->redirs);
			return (EXIT_FAILURE);
		}
	}
	if ((*token_node)->next)
		*token_node = (*token_node)->next;
	return (EXIT_SUCCESS);
}

static int	handle_pipe(t_cmd **current_cmd)
{
	t_cmd	*new_command;

	if (current_cmd == NULL || *current_cmd == NULL)
		return (EXIT_FAILURE);
	if (!(*current_cmd)->redirs)
	{
		(*current_cmd)->redirs = init_redirection();
		if (!(*current_cmd)->redirs)
			return (EXIT_FAILURE);
	}
	(*current_cmd)->redirs->out_type = RD_PIPE;
	new_command = create_new_command(NULL);
	if (!new_command)
		return (EXIT_FAILURE);
	new_command->redirs = init_redirection();
	if (!new_command->redirs)
	{
		free(new_command);
		return (EXIT_FAILURE);
	}
	new_command->redirs->in_type = RD_PIPE;
	(*current_cmd)->next = new_command;
	*current_cmd = new_command;
	return (EXIT_SUCCESS);
}

static int	is_redirection_token(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == TK_REDIRECT_IN || token->type == TK_REDIRECT_OUT
			|| token->type == TK_APPEND_OUT || token->type == TK_HEREDOC)
		return (1);
	return (0);
}

static t_redirs	*init_redirection(void)
{
	t_redirs	*new_redir;

	new_redir = malloc(sizeof(t_redirs));
	if (!new_redir)
		return (NULL);
	new_redir->in_type = RD_STD;
	new_redir->out_type = RD_STD;
	new_redir->infile_name = NULL;
	new_redir->outfile_name = NULL;
	new_redir->heredoc_delimiter = NULL;
	new_redir->heredoc_content = NULL;
	new_redir->fds[0] = 0;
	new_redir->fds[1] = 1;
	new_redir->append_mode = 0;
	return (new_redir);
}

static t_token	*get_current_token(t_list *token_list)
{
	if (token_list)
		return ((t_token *)(token_list->content));
	return (NULL);
}

static t_token	*get_next_token(t_list *token_list)
{
	if (token_list && token_list->next)
		return ((t_token *)(token_list->next->content));
	return (NULL);
}

static int	count_argv_size(char **argv)
{
	int	size;

	if (argv == NULL)
		return (0);
	size = 0;
	while (argv[size])
		size++;
	return (size);
}
