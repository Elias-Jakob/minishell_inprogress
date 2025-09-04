#include "../../includes/minishell.h"

int	exec_builtin(t_exec_context *exec_context, t_cmd *builtin)
{
	(void)exec_context;
	int	exit_status;
	int	out_fd;

	out_fd = STDOUT_FILENO;
	if (builtin->redirs)
		out_fd = builtin->redirs->fds[1];
	exit_status = 0;
	if (!ft_strncmp("echo", builtin->argv[0], 4))
		exit_status = echo(builtin, out_fd);
	else if (!ft_strncmp("cd", builtin->argv[0], 2))
		exit_status = cd(builtin);
	return (exit_status);
}

int	launch_child_process(t_exec_context *exec_context, t_cmd *command)
{
	char	*cmd_path;
	int		exit_status;
	// 1. setup_fds
	// 2. fork
	// 3. make redirections
	// 4. look up the path to the binary
	// 5. execve
	exit_status = 1;
	command->pid = fork();
	if (command->pid == -1)
		fatal_error(exec_context, "fork failed");
	else if (command->pid == 0) // child
	{
		cmd_path = look_up_cmdpath(command->argv[0], exec_context->paths, &exit_status);
		if (cmd_path)
		{
			if (command->redirs)
				setup_redirections(command->redirs);
			execve(cmd_path, command->argv, exec_context->envp);
			perror(command->argv[0]);
			free(cmd_path);
		}
		clean_up_commands(exec_context);
		exit(exit_status);
	}
	// parent (closing fds we dont need)
	if (command->redirs)
	{
		if (command->redirs->fds[0] != STDIN_FILENO
			&& close(command->redirs->fds[0]) == -1)
			fatal_error(exec_context, "close failed");
		if (command->redirs->fds[1] != STDOUT_FILENO
			&& close(command->redirs->fds[1]) == -1)
			fatal_error(exec_context, "close failed");
	}
	return (command->pid);
}
