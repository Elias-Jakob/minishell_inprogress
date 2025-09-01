#include "../../includes/minishell.h"

int parse_command(t_list **current_tk_list, t_cmd **cmd_head, int pipe_in);

void	init_cmd(t_cmd *cmd, int pipe_in)
{
    ft_memset(cmd, 0, sizeof(t_cmd));
    if (pipe_in)
    {
        init_redirs_if_needed(cmd);
        cmd->redirs->in_type = RD_PIPE;
    }
}

int	allocate_cmd_argv(t_cmd *cmd, t_list *current)
{
    int     argv_count;

    argv_count = get_argv_amount(current);
    if (argv_count > 0)
    {
        cmd->argv = malloc(sizeof(char *) * (argv_count + 1));
        if (!cmd->argv)
            return (EXIT_FAILURE);
    }
	return (EXIT_SUCCESS);
}

void	handle_word(t_cmd *cmd, t_token *token, size_t *i)
{
	cmd->argv[*i] = ft_strdup(token->value);
	(*i)++;
}

t_list *handle_redirection(t_cmd *cmd, t_list *current)
{
	return (parse_redirection(cmd, current));
}

void	finalize_cmd(t_cmd *cmd, t_cmd **cmd_head, size_t i)
{
	t_cmd	*new_cmd;

	if (cmd->argv)
		cmd->argv[i] = NULL;
	if (cmd->argv || cmd->redirs)
	{
		new_cmd = malloc(sizeof(t_cmd));
		if (!new_cmd)
			return ;
		*new_cmd = *cmd;
		new_cmd->next = NULL;
		append_cmd(cmd_head, new_cmd);
	}
}

int	handle_pipe(t_cmd *cmd, t_cmd **cmd_head, size_t i)
{
	init_redirs_if_needed(cmd);
	cmd->redirs->out_type = RD_PIPE;
	if (cmd->argv)
		cmd->argv[i] = NULL;
	finalize_cmd(cmd, cmd_head, i);
	return (EXIT_SUCCESS);
}

t_list	*process_token(t_cmd *cmd, t_list *current, size_t *i, t_cmd **cmd_head, int *is_redir)
{
	t_token	*token;
	t_list	*next;
	
	token = (t_token *)current->content;
	if (!token)
		return (current->next);
	if (is_token_word(token->type))
	{
		handle_word(cmd, token, i);
		return (current->next);
	}
	if (token->type == TK_PIPE)
    {
        handle_pipe(cmd, cmd_head, *i);
		*is_redir = 1;
        return (current->next);
    }
	if (is_token_redirect(token->type))
	{
		next = handle_redirection(cmd, current);
		if (!next || next == current)
			return (current->next); 
		return (next);
	}
	return (current->next);
}


int parse_command(t_list **current_tk_list, t_cmd **cmd_head, int pipe_in)
{
	t_list	*current;
	t_cmd	cmd;
	size_t	i;
	int		is_redir;

	is_redir = 0;
	current = *current_tk_list;
	init_cmd(&cmd, pipe_in);
	if (allocate_cmd_argv(&cmd, current) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = 0;
	while (current)
	{
		current = process_token(&cmd, current, &i, cmd_head, &is_redir);
		if (is_redir == 1)
			break;
	}
	if (!is_redir)
		finalize_cmd(&cmd, cmd_head, i);
	*current_tk_list = current;
	if (is_redir && current)
		return (parse_command(current_tk_list, cmd_head, 1));
	return (EXIT_SUCCESS);
}

int parser(t_list *token_list, t_cmd **cmd_head)
{
	t_list	*current;
	current = token_list;
	
	while (current)
		if (parse_command(&current, cmd_head, 0) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
