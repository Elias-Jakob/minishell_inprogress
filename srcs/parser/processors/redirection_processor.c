#include "../../../includes/minishell.h"

static int	setup_redirection_context(t_list **token_node, t_cmd **current_cmd,
									 t_cmd **cmd_head, t_token **redir,
									 t_token **target)
{
	if (validate_redirection_sequence(*token_node) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*redir = get_current_token(*token_node);
	*target = get_next_token(*token_node);
	if (ensure_current_command_exists(current_cmd, cmd_head) == NULL)
		return (EXIT_FAILURE);
	if (ensure_redirection_exists(*current_cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	dispatch_redirection_by_type(t_token *redir, t_token *target,
										t_cmd *cmd)
{
	if (redir->type == TK_REDIRECT_IN)
		return (handle_input_redirection(cmd, target));
	else if (redir->type == TK_REDIRECT_OUT)
		return (handle_output_redirection(cmd, target));
	else if (redir->type == TK_APPEND_OUT)
		return (handle_append_redirection(cmd, target));
	else if (redir->type == TK_HEREDOC)
		return (handle_heredoc_redirection(cmd, target));
	return (EXIT_FAILURE);
}

int	process_redirection_token(t_list **token_node, t_cmd **current_cmd, t_cmd **cmd_head)
{
	t_token	*token_redir;
	t_token	*token_target;

	if (setup_redirection_context(token_node, current_cmd, cmd_head,
								&token_redir, &token_target) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (dispatch_redirection_by_type(token_redir, token_target, *current_cmd)
		== EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((*token_node)->next)
		*token_node = (*token_node)->next;
	return (EXIT_SUCCESS);
}
