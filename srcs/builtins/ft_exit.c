#include "../../includes/minishell.h"

int	ft_exit(t_cmd *cmd, int out_fd)
{
	int	i;
	int	err_fd;

	if (!cmd->argv[1])
		return (0);
	err_fd = out_fd;
	if (out_fd == STDOUT_FILENO)
		err_fd = 2;
	if (cmd->argv[1] && cmd->argv[2])
		return (ft_putstr_fd("exit: too many arguments\n", err_fd), 1);
	i = 0;
	if (cmd->argv[1][i] == '+' || cmd->argv[1][i] == '-')
		i++;
	while (cmd->argv[1][i])
	{
		if (!ft_isdigit(cmd->argv[1][i]))
			return (ft_putstr_fd("exit: ", err_fd),
				ft_putstr_fd(cmd->argv[1], err_fd),
				ft_putstr_fd(": numeric argument required\n", err_fd), 2);
		i++;
	}
	return (ft_atoi(cmd->argv[1]));
}
