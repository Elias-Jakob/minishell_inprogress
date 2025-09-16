#include "../../includes/minishell.h"

static int	is_env_name(char *env_name, char *name)
{
	size_t	env_name_len;
	size_t	name_len;

	name_len = ft_strlen(name);
	if (ft_strncmp(env_name, name, name_len))
		return (0);
	env_name_len = ft_strlen(env_name);
	if (name_len < env_name_len && env_name[name_len] != '=')
		return (0);
	return (1);
}

void	print_env(t_exec_context *exec_context, int out_fd)
{
	size_t	len;

	if (!exec_context->envp)
		return ;
	len = 0;
	while (exec_context->envp[len])
	{
		ft_putstr_fd(exec_context->envp[len++], out_fd);
		ft_putstr_fd("\n", out_fd);
	}
}

size_t	env_len(char **arr)
{
	size_t	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

char	**look_up_envname(t_exec_context *exec_context, char *name)
{
	size_t	i;
	size_t	name_len;

	if (!exec_context->envp)
		return (NULL);
	i = 0;
	name_len = 0;
	while (name[name_len] && name[name_len] != '=')
		name_len++;
	while (exec_context->envp[i])
	{
		if (!strncmp(exec_context->envp[i], name, name_len))
			return ((exec_context->envp) + i);
		i++;
	}
	return (NULL);
}

int	modify_envp(t_exec_context *ctx, int s, char *name)
{
	char	**new_env;
	size_t	i;
	int		offset;

	new_env = (char **)malloc(sizeof(char *) * (env_len(ctx->envp) + 1 + s));
	if (!new_env)
		return (perror("envp: malloc failed"), 0);
	i = 0;
	offset = 0;
	while (ctx->envp[i + offset])
	{
		if (name && is_env_name(ctx->envp[i + offset], name))
			offset = 1;
		if (!ctx->envp[i + offset])
			break ;
		new_env[i] = ft_strdup(ctx->envp[i + offset]);
		if (!new_env[i++])
			return (free_str_arr(new_env), perror("envp: ft_strdup failed"), 0);
	}
	if (name && s > 0)
		new_env[i++] = name;
	new_env[i] = NULL;
	free_str_arr(ctx->envp);
	ctx->envp = new_env;
	return (1);
}
