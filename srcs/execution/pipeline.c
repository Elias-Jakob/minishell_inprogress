#include "../../includes/minishell.h"

static void	set_exit_status(t_pipeline *pipeline, int finished_pid, int status)
{
	t_cmd	*current_cmd;

	current_cmd = pipeline->commands;
	while (current_cmd)
	{
		if (current_cmd->pid == finished_pid)
			break ;
		current_cmd = current_cmd->next;
	}
	current_cmd->exit_status = 0;
	if (WIFEXITED(status))
		current_cmd->exit_status = WEXITSTATUS(status);
}

static void	wait_on_children(
	t_pipeline *pipeline, t_exec_context *exec_context)
{
	int	status;
	t_cmd	*current_cmd;
	t_cmd	*last_cmd;
	pid_t	finished_pid;

	current_cmd = pipeline->commands;
	while (current_cmd)
	{
		if (current_cmd->is_builtin)
		{
			finished_pid = wait(&status);
			if (finished_pid == -1)
				error_and_exit("wait failed", 1);
			set_exit_status(pipeline, finished_pid, status);
		}
		if (!current_cmd->next)
			last_cmd = current_cmd;
		current_cmd = current_cmd->next;
	}
	exec_context->exit_status = last_cmd->exit_status;
}

void	run_pipeline(t_pipeline *pipeline, t_exec_context *exec_context)
{
	t_cmd	*current_cmd;

	current_cmd = pipeline->commands;
	while (current_cmd)
	{
		if (current_cmd->is_builtin)
			exec_builtin(pipeline, exec_context, current_cmd);
		else
			exec_command(exec_context, current_cmd);
		current_cmd = current_cmd->next;
	}
	// wait for all processes
	wait_on_children(pipeline, exec_context);
}
