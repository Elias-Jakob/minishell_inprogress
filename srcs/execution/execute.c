#include "../../includes/minishell.h"

int	exec_builtin(
	t_pipline *pipeline, t_exec_context exec_context, t_cmd *builtin)
{
	// 1. make redirs
	// 2. call builtin function
	return (0);
}

int	exec_command(
	t_pipline *pipeline, t_exec_context exec_context, t_cmd *command)
{
	char	*cmd_path;
	// 1. fork
	// 2. look up the path to the binary
	// 3. make redirs - up to this point i dont consider pipes
	// 4. execve
	command->pid = fork();
	if (command->pid == -1)
		return (perror("fork failed"), -1);
	else if (command->pid == 0) // child
	{
		pathname = look_up_cmdpath(command->argv[0], exec_context->paths);
		if (!pathname)
			exit(127);
		redirect_in(command->redirs);
		redirect_out(command->redirs);
		execve(cmd_path, command->argv, command->envp);
		perror("execve failed");
		free(cmd_path);
		exit(1);
	}
	// parent
	return (command->pid);
}
