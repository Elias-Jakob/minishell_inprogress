#include "../../includes/minishell.h"

static int	change_dir(char *dest, int free_dest)
{
	int	exit_status;

	exit_status = 0;
	if (chdir(dest) == -1)
	{
		perror("cd: chdir failed");
		exit_status = 1;
	}
	if (free_dest)
		free(dest);
	// TODO: update environment variable OLDPWD
	// set_env("OLDPWD", getcwd(NULL, 0));
	return (exit_status);
}

static int	is_dest_valid(char *dest_path)
{
	if (access(dest_path, X_OK) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(dest_path, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}

static int	cd_expand(char *arg, char *env_var, int out_fd)
{
	char	*dest_path;
	char	*path;
	int		exit_status;
	int		is_tilde;

	path = getenv(env_var);
	if (!path)
		return (0);
	is_tilde = 0;
	if (arg)
	{
		dest_path = ft_strjoin(path, arg);
		if (!dest_path)
			return (perror("cd: ft_strjoin failed"), 1);
		is_tilde = 1;
	}
	else
		dest_path = path;
	if (!is_dest_valid(dest_path))
		return (1);
	exit_status = change_dir(dest_path, is_tilde);
	if (!ft_strncmp("OLDPWD", env_var, 6))
		ft_pwd(NULL, out_fd);
	return (exit_status);
}

int	ft_cd(t_cmd *cmd, int out_fd)
{
	char	*path;

	path = cmd->argv[1];
	if (!path)
		return (cd_expand(NULL, "HOME", out_fd));
	else if (path[0] == '-' && path[1] == '\0')
		return (cd_expand(NULL, "OLDPWD", out_fd));
	else if (path[0] == '~')
	{
		path++;
		if (path[0] == '/')
			return (cd_expand(path, "HOME", out_fd));
	}
	if (!is_dest_valid(path))
		return (1);
	return (change_dir(path, 0));
}
