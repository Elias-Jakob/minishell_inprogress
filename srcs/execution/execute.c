#include "../../includes/minishell.h"

static void	free_str_arr(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static char	*check_full_path(char *cmd)
{
	char	*pathname;

	if (access(cmd, F_OK) == 0)
	{
		pathname = ft_strdup(cmd);
		if (!pathname)
			return (perror("ft_strdup failed"), NULL);
		return (pathname);
	}
	return (perror(cmd), NULL);
}

static char	*find_executable(char *cmd, char **dirs)
{
	size_t	i;
	char	*path;
	char	*pathname;

	i = 0;
	while (dirs && dirs[i])
	{
		path = ft_strjoin(dirs[i], "/");
		if (!path)
			return (free_str_arr(dirs), perror("ft_strjoin failed"), NULL);
		pathname = ft_strjoin(path, cmd);
		if (!pathname)
			return (free_str_arr(dirs), free(path),
				perror("ft_strjoin failed"), NULL);
		if (access(pathname, F_OK) == 0)
			return (free_str_arr(dirs), free(path), pathname);
		free(path);
		free(pathname);
		i++;
	}
	free_str_arr(dirs);
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}

static char	*look_up_cmdpath(char *cmd, char *paths)
{
	char	**bin_dirs;

	if (!cmd || !paths)
		return (ft_putstr_fd("command not found:  \n", 2), NULL);
	if (ft_strchr(cmd, '/'))
		return (check_full_path(cmd));
	bin_dirs = ft_split(paths, ':');
	if (!bin_dirs)
		return (perror("ft_split failed"), NULL);
	return (find_executable(cmd, bin_dirs));
}

int	exec_builtin(
	t_pipeline *pipeline, t_exec_context *exec_context, t_cmd *builtin)
{
	(void)pipeline;
	(void)exec_context;
	(void)builtin;
	// 1. make redirs
	// 2. call builtin function
	return (0);
}

int	exec_command(t_exec_context *exec_context, t_cmd *command)
{
	char	*cmd_path;
	// 1. setup_fds
	// 2. fork
	// 3. make redirections
	// 4. look up the path to the binary
	// 5. execve
	if (command->redirs)
	{
		set_in_fd(command, command->redirs);
		set_out_fd(command, command->redirs);
	}
	command->pid = fork();
	if (command->pid == -1)
		error_and_exit("fork failed", 1);
	else if (command->pid == 0) // child
	{
		cmd_path = look_up_cmdpath(command->argv[0], exec_context->paths);
		if (!cmd_path)
			exit(127);
		if (command->redirs)
			setup_redirections(command->redirs);
		execve(cmd_path, command->argv, exec_context->envp);
		perror("execve failed");
		free(cmd_path);
		exit(1);
	}
	// parent (closing fds we dont need)
	if (command->redirs->fds[0] != STDIN_FILENO && close(command->redirs->fds[0]) == -1)
		error_and_exit("close failed", 1);
	if (command->redirs->fds[1] != STDOUT_FILENO && close(command->redirs->fds[1]) == -1)
		error_and_exit("close failed", 1);
	return (command->pid);
}
