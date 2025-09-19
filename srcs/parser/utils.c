#include "../../includes/minishell.h"

int	ensure_redirection_exists(t_cmd *cmd)
{
	if (cmd->redirs == NULL)
	{
		cmd->redirs = init_redirection();
		if (cmd->redirs == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	validate_redirection_sequence(t_list *token_node)
{
	t_token	*next_token;

	next_token = get_next_token(token_node);
	if (next_token == NULL)
	{
		printf("minishell: syntax error: expected filename after redirection\n");
		return (EXIT_FAILURE);
	}
	if (is_redirection_token(next_token) || next_token->type == TK_PIPE)
	{
		printf("minishell: syntax error: unexpected token after redirection\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	validate_pipe_sequence(t_list *token_node)
{
	t_token	*next_token;

	next_token = get_next_token(token_node);
	if (next_token == NULL)
	{
		printf("minishell: syntax error: unexpected end of input after pipe\n");
		return (EXIT_FAILURE);
	}
	if (next_token->type == TK_PIPE)
	{
		printf("minishell: syntax error: unexpected pipe after pipe\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	validate_token_sequence(t_list *token_list)
{
	t_list	*current;
	t_token	*token;

	if (!token_list)
		return (EXIT_SUCCESS);
	current = token_list;
	token = (t_token *)current->content;
	if (token->type == TK_PIPE)
	{
		printf("minishell: syntax error: unexpected pipe at beginning\n");
		return (EXIT_FAILURE);
	}
	while (current)
	{
		token = (t_token *)current->content;
		if (token->type == TK_PIPE && validate_pipe_sequence(current) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (is_redirection_token(token) && validate_redirection_sequence(current) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	add_argument_to_command(t_cmd *cmd, t_token *token, char **env, int last_exit_status)
{
	int		count;
	char	**new_argv;
	char	*expanded_value;

	if (cmd == NULL || token == NULL)
		return (EXIT_FAILURE);
	count = count_argv_size(cmd->argv);
	new_argv = realloc(cmd->argv, sizeof(char *) * (count + 2));
	if (new_argv == NULL)
		return (EXIT_FAILURE);
	cmd->argv = new_argv;
	expanded_value = process_token_expansion(token, env, last_exit_status);
	if (expanded_value)
		cmd->argv[count] = expanded_value;
	else
	{
		cmd->argv[count] = ft_strdup(token->value);
	}
	if (cmd->argv[count] == NULL)
		return (EXIT_FAILURE);
	cmd->argv[count + 1] = NULL;
	return (EXIT_SUCCESS);
}

int	count_argv_size(char **argv)
{
	int	size;

	if (argv == NULL)
		return (0);
	size = 0;
	while (argv[size])
		size++;
	return (size);
}

t_redirs	*init_redirection(void)
{
	t_redirs	*new_redir;

	new_redir = malloc(sizeof(t_redirs));
	if (new_redir == NULL)
		return (NULL);
	new_redir->in_type = RD_STD;
	new_redir->out_type = RD_STD;
	new_redir->infile_name = NULL;
	new_redir->outfile_name = NULL;
	new_redir->heredoc_content = NULL;
	new_redir->heredoc_delimiter = NULL;
	new_redir->fds[0] = 0;
	new_redir->fds[1] = 1;
	new_redir->append_mode = 0;
	return (new_redir);
}

