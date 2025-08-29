#include "../../includes/minishell.h"

int	run_pipeline(t_pipeline *pipeline, t_exec_context *exec_context)
{
	t_cmd	*current_cmd;

	current_cmd = pipeline->commands;
	while (current_cmd)
	{
		if (current_cmd->is_builtin)
			exec_builtin(pipeline, exec_context, current_cmd);
		else
			exec_cmd(pipeline, exec_context, current_cmd);
		current_cmd->next;
	}
	// wait for all processes
}
