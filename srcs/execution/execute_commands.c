#include "../../includes/minishell.h"

static void	set_cmd_exit_status(t_exec_context *exec_context, int finished_pid, int status)
{
	t_cmd	*current_cmd;

	current_cmd = exec_context->commands;
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

static void	wait_on_children(t_exec_context *exec_context)
{
	int	status;
	t_cmd	*current_cmd;
	t_cmd	*last_cmd;
	pid_t	finished_pid;

	exec_context->exit_status = 0;
	current_cmd = exec_context->commands;
	if (!current_cmd)
		return ;
	while (current_cmd)
	{
		if (!current_cmd->is_builtin)
		{
			finished_pid = wait(&status);
			if (finished_pid == -1)
				fatal_error(exec_context, "wait failed");
			set_cmd_exit_status(exec_context, finished_pid, status);
		}
		if (!current_cmd->next)
			last_cmd = current_cmd;
		current_cmd = current_cmd->next;
	}
	exec_context->exit_status = last_cmd->exit_status;
}

void	exec_command_list(t_exec_context *exec_context)
{
	t_cmd	*command;

	command = exec_context->commands;
	while (command)
	{
		if (command->redirs)
		{
			set_in_fd(exec_context, command, command->redirs);
			set_out_fd(exec_context, command, command->redirs);
		}
		if (command->is_builtin)
			exec_builtin(exec_context, command);
		else
			launch_child_process(exec_context, command);
		command = command->next;
	}
	// wait for all processes
	wait_on_children(exec_context);
	// return exit status
	// clean up the pipeline
}
