#include "../../includes/minishell.h"

int	ft_env(t_exec_context *exec_context, t_cmd *cmd, int out_fd)
{
	(void)cmd;
	print_env(exec_context, out_fd);
	return (0);
}
