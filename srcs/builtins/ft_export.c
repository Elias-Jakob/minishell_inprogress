#include "../../includes/minishell.h"

int	check_arg(char *arg)
{
	size_t	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] == '=')
			break ;
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static char	*create_new_name(char *arg, char **is_name)
{
	char	*new_name;
	char	*eq_sign;

	eq_sign = ft_strchr(arg, '=');
	if (!eq_sign && !is_name)
		new_name = ft_strjoin(arg, "=''");
	else if (eq_sign && *(eq_sign + 1) == '\0')
		new_name = ft_strjoin(arg, "''");
	else
		new_name = ft_strdup(arg);
	if (!new_name)
		return (perror("export: malloc failed"), NULL);
	return (new_name);
}

static void	export_name(t_exec_context *exec_context, char *arg)
{
	char	**name;
	char	*new_name;

	name = look_up_envname(exec_context, arg);
	if (name && !ft_strchr(arg, '='))
		return ;
	new_name = create_new_name(arg, name);
	if (!new_name)
		fatal_error(exec_context, "");
	if (!name)
	{
		if (!modify_envp(exec_context, 1, new_name))
			fatal_error(exec_context, "");
	}
	else
	{
		free(*name);
		*name = new_name;
	}
}

int	ft_export(t_exec_context *exec_context, t_cmd *cmd, int out_fd)
{
	size_t	n_arg;
	int		exit_status;

	exit_status = 0;
	if (!cmd->argv[1])
		return (print_env(exec_context, out_fd), exit_status);
	n_arg = 1;
	while (cmd->argv[n_arg])
	{
		if (check_arg(cmd->argv[n_arg]))
			export_name(exec_context, cmd->argv[n_arg]);
		else
		{
			ft_putstr_fd("export: not an identifier: ", 2);
			ft_putstr_fd(cmd->argv[n_arg], 2);
			ft_putchar_fd('\n', 2);
			exit_status = 1;
		}
		n_arg++;
	}
	return (exit_status);
}
