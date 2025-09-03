#include "../../includes/minishell.h"

int	echo(t_cmd *cmd, int out_fd)
{
	int	n_flag;
	size_t	i;

	i = 1;
	if (!cmd->argv[i])
		return (write(out_fd, "\n", 1) < 0);
	n_flag = 0;
	if (!ft_strncmp(cmd->argv[i], "-n", 2) && cmd->argv[i][2] == '\0')
		n_flag = 1;
	if (!ft_strncmp(cmd->argv[i + n_flag], "-", 1)
		&& cmd->argv[i + n_flag][1] == '\0')
		i++;
	while (cmd->argv[i + n_flag])
	{
		if (write(out_fd, cmd->argv[i + n_flag],
			ft_strlen(cmd->argv[i + n_flag])) == -1)
			return (1);
		if (cmd->argv[i + n_flag + 1] && write(out_fd, " ", 1) == -1)
			return (1);
		i++;
	}
	if (!n_flag)
		return (write(out_fd, "\n", 1) < 0);
	return (0);
}
