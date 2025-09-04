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
	return (exit_status);
}

static int	is_dest_valid(char *dest, char *dest_path)
{
	if (access(dest_path, X_OK) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(dest, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}

static int	cd_relative(t_cmd *cmd)
{
	char	*cwd;
	char	*path;
	char	*dest_path;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("cd: getcwd failed"), 1);
	path = ft_strjoin("/", cmd->argv[1]);
	if (!path)
		return (free(cwd), perror("cd: ft_strjoin failed"), 1);
	dest_path = ft_strjoin(cwd, path);
	if (!dest_path)
		return (free(cwd), free(path), perror("cd: ft_strjoin failed"), 1);
	free(cwd);
	free(path);
	if (is_dest_valid(cmd->argv[1], dest_path))
		return (change_dir(dest_path, 1));
	free(dest_path);
	return (1);
}

static int	cd_defaults(char *minus, int out_fd)
{
	// -         When a <hyphen-minus> is used as the operand, this shall be equivalent to the command:
	//
	//               cd "$OLDPWD" && pwd
	//
	//           which changes to the previous working directory and then writes its name.
	char	*dest_path;
	int		exit_status;

	if (!minus)
		dest_path = getenv("HOME");
	else
		dest_path = getenv("OLDPWD");
	if (!dest_path)
		return (0);
	if (!is_dest_valid(NULL, dest_path))
		return (1);
	// TODO: if minus: cd OLDPWD && pwd
	exit_status = change_dir(dest_path, 0);
	if (minus)
		pwd(NULL, out_fd);
	return (exit_status);
}

int	cd(t_cmd *cmd, int out_fd)
{
	// TODO: expande ~ to HOME
	// change dir to home if no arguments or - to OLDPWD
	if (!cmd->argv[1] ||
		(cmd->argv[1][0] == '-' && cmd->argv[1][1] == '\0'))
		return (cd_defaults(cmd->argv[1], out_fd));
	// change dir absolute path
	if (cmd->argv[1][0] == '/')
	{
		if (!is_dest_valid(cmd->argv[1], cmd->argv[1]))
			return (1);
		return (change_dir(cmd->argv[1], 0));
	}
	// change path relative path
	return (cd_relative(cmd));
}
