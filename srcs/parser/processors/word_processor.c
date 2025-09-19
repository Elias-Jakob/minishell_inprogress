#include "../../../includes/minishell.h"

int	process_word_token(t_token *token, t_cmd **current_cmd, t_cmd **cmd_head,
					   char **env, int last_exit_status)
{
	if (*current_cmd == NULL)
	{
		*current_cmd = create_new_command(token);
		if (*current_cmd == NULL)
			return (EXIT_FAILURE);
		return (append_command_to_list(*current_cmd, cmd_head));
	}
	return (add_argument_to_command(*current_cmd, token, env, last_exit_status));
}
