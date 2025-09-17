#include "../../includes/minishell.h"

int	ft_unset(t_exec_context *exec_context, t_cmd *cmd)
{
	size_t	n_arg;
	int		exit_status;

	if (!cmd->argv[1])
		return (ft_putstr_fd("unset: not enough arguments\n", 2), 1);
	n_arg = 0;
	exit_status = 0;
	while (cmd->argv[++n_arg])
	{
		if (check_arg(cmd->argv[n_arg]))
		{
			if (look_up_envname(exec_context, cmd->argv[n_arg])
				&& !modify_envp(exec_context, -1, cmd->argv[n_arg]))
				fatal_error(exec_context, "");
		}
		else
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(cmd->argv[n_arg], 2);
			ft_putstr_fd(": invalid parameter name\n", 2);
			exit_status = 1;
		}
	}
	return (exit_status);
}
