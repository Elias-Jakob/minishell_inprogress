#include "../../includes/minishell.h"

int	ft_pwd(t_cmd *cmd, int out_fd)
{
	char	*cwd;

	if (cmd && cmd->argv[1])
		return (ft_putstr_fd("pwd: too many arguments\n", 2), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("pwd: getcwd failed"), 1);
	ft_putstr_fd(cwd, out_fd);
	ft_putstr_fd("\n", out_fd);
	free(cwd);
	return (0);
}
