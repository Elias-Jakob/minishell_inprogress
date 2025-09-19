#include "../../../includes/minishell.h"

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
