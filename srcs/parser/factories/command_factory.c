#include "../../../includes/minishell.h"

int	add_argument_to_command(t_cmd *cmd, t_token *token, char **env,
							int exit_status)
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
	expanded_value = process_token_expansion(token, env, exit_status);
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

