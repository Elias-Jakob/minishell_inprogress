#include "../../includes/minishell.h"

static int	check_arg(char *arg)
{
	if (arg[0] == '-')
	{
		ft_putstr_fd("unset: ", 2);
		write(2, arg, 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (0);
	}
	return (1);
}

int	ft_unset(t_exec_context *exec_context, t_cmd *cmd)
{
	size_t	n_arg;

	n_arg = 1;
	while (cmd->argv[n_arg])
	{
		if (check_arg(cmd->argv[n_arg]))
		{
			if (look_up_envname(exec_context, cmd->argv[n_arg])
				&& !modify_envp(exec_context, -1, cmd->argv[n_arg]))
				fatal_error(exec_context, "");
		}
		else
			return (2);
		n_arg++;
	}
	return (0);
}
