#include "../../../includes/parser.h"

t_cmd	*ensure_current_command_exists(t_cmd **current_cmd, t_cmd **cmd_head)
{
	if (*current_cmd == NULL)
	{
		*current_cmd = create_new_command(NULL);
		if (*current_cmd == NULL)
			return (NULL);
		if (append_command_to_list(*current_cmd, cmd_head) == EXIT_FAILURE)
			return (NULL);
	}
	return (*current_cmd);
}

int	append_command_to_list(t_cmd *new_cmd, t_cmd **cmd_head)
{
	t_cmd	*last;

	if (*cmd_head == NULL)
	{
		*cmd_head = new_cmd;
		return (EXIT_SUCCESS);
	}
	last = *cmd_head;
	while (last->next)
		last = last->next;
	last->next = new_cmd;
	return (EXIT_SUCCESS);
}

t_cmd	*create_new_command(t_token *token)
{
	t_cmd	*new_command;

	new_command = malloc(sizeof(t_cmd));
	if (new_command == NULL)
		return (NULL);
	new_command->argv = NULL;
	new_command->redirs = NULL;
	new_command->pid = 0;
	new_command->is_builtin = 0;
	new_command->exit_status = 0;
	new_command->next = NULL;
	if (token)
	{
		new_command->argv = malloc(sizeof(char *) * 2);
		if (new_command->argv == NULL)
		{
			free(new_command);
			return (NULL);
		}
		new_command->argv[0] = ft_strdup(token->value);
		if (new_command->argv[0] == NULL)
		{
			free(new_command->argv);
			free(new_command);
			return (NULL);
		}
		new_command->argv[1] = NULL;
		if (is_token_builtin(token) == EXIT_SUCCESS)
			new_command->is_builtin = 1;
	}
	return (new_command);
}
