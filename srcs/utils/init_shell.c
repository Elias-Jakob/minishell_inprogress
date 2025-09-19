#include "../../includes/minishell.h"

void	init_context(t_exec_context *exec_context, char **envp)
{
	setup_signals();
	exec_context->exit_status = 0;
	exec_context->paths = getenv("PATH");
	exec_context->envp = copy_envp(envp);
	if (!exec_context->envp)
		exit(1);
}
