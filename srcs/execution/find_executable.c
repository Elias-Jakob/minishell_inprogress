#include "../../includes/minishell.h"

// INFO: This code could be better if we are allowed to use the global errno
// then i just would need to check if a file with the pathname exists return it
// and let the error handling happen with execve by checking errno

static char	*check_full_path(char *cmd, int *err_status)
{
	char	*pathname;

	*err_status = 127;
	if (access(cmd, F_OK) == 0)
	{
		pathname = ft_strdup(cmd);
		if (!pathname)
			return (perror("ft_strdup failed"), NULL);
		if (access(cmd, X_OK) == 0)
			return (pathname);
		*err_status = 126;
		free(pathname);
	}
	return (ft_putstr_fd("bby_shell: ", 2), perror(""), ft_putstr_fd(cmd, 2), NULL);
}

static char	*search_paths(char *cmd, char **dirs)
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
	ft_putstr_fd("bby_shell: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}

char	*look_up_cmdpath(char *cmd, char *paths, int *err_status)
{
	char	**bin_dirs;
	char	*cmd_path;

	if (!cmd || !paths)
		return (*err_status = 127, ft_putstr_fd("bby_shell: command not found:  \n", 2), NULL);
	if (ft_strchr(cmd, '/'))
		return (check_full_path(cmd, err_status));
	bin_dirs = ft_split(paths, ':');
	if (!bin_dirs)
		return (perror("ft_split failed"), NULL);
	cmd_path = search_paths(cmd, bin_dirs);
	if (!cmd_path)
		*err_status = 127;
	if (cmd_path && access(cmd_path, X_OK) == -1)
	{
		*err_status = 126;
		perror(cmd);
		free(cmd_path);
		cmd_path = NULL;
	}
	return (cmd_path);
}
