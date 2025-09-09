#include "../../includes/parser.h"

int	process_word_token(t_token *token, t_cmd **current_cmd, t_cmd **cmd_head, char **env)
{
	if (!*current_cmd)
	{
		*current_cmd = create_new_command(token);
		if (*current_cmd == NULL)
			return (EXIT_FAILURE);
		return (append_command_to_list(*current_cmd, cmd_head));
	}
	return (add_argument_to_command(*current_cmd, token, env));
}

int	process_pipe_token(t_cmd **current_cmd)
{
	t_cmd	*new_cmd;

	if (*current_cmd == NULL)
		return (EXIT_FAILURE);
	if (ensure_redirection_exists(*current_cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	(*current_cmd)->redirs->out_type = RD_PIPE;
	new_cmd = create_new_command(NULL);
	if (new_cmd == NULL)
		return (EXIT_FAILURE);
	if (ensure_redirection_exists(new_cmd) == EXIT_FAILURE)
	{
		free(new_cmd);
		return (EXIT_FAILURE);
	}
	new_cmd->redirs->in_type = RD_PIPE;
	(*current_cmd)->next = new_cmd;
	*current_cmd = new_cmd;
	return (EXIT_SUCCESS);
}

int	process_redirection_token(t_list **token_node, t_cmd **current_cmd, t_cmd **cmd_head)
{
	t_token	*token_redir;
	t_token	*token_target;

	if (validate_redirection_sequence(*token_node) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	token_redir = get_current_token(*token_node);
	token_target = get_next_token(*token_node);
	if (ensure_current_command_exists(current_cmd, cmd_head) == NULL)
		return (EXIT_FAILURE);
	if (ensure_redirection_exists(*current_cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (token_redir->type == TK_REDIRECT_IN)
	{
		if (handle_input_redirection(*current_cmd, token_target) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (token_redir->type == TK_REDIRECT_OUT)
	{
		if (handle_output_redirection(*current_cmd, token_target) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (token_redir->type == TK_APPEND_OUT)
	{
		if (handle_append_redirection(*current_cmd, token_target) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (token_redir->type == TK_HEREDOC)
	{
		if (handle_heredoc_redirection(*current_cmd, token_target) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if ((*token_node)->next)
		*token_node = (*token_node)->next;
	return (EXIT_SUCCESS);
}

