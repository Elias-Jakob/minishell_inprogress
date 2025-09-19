#include "../../includes/minishell.h"

char	**copy_envp(char **envp)
{
	char	**alloc_envp;
	size_t	arr_len;
	size_t	i;

	arr_len = env_len(envp);
	alloc_envp = (char **)malloc(sizeof(char *) * (arr_len + 1));
	if (!alloc_envp)
		return (perror("init_envp: malloc failed"), NULL);
	i = 0;
	while (i < arr_len)
	{
		alloc_envp[i] = ft_strdup(envp[i]);
		if (!alloc_envp[i])
			return (free_str_arr(alloc_envp),
			perror("init_envp: ft_strdup failed"), NULL);
		i++;
	}
	alloc_envp[i] = NULL;
	return (alloc_envp);
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

char	*expand_variables(char *str, char **env)
{
	char	*new_str;

	new_str = get_env_value(env, str);
	if (new_str == NULL)
		return (str);
	printf("Gotten env val: %s\n", new_str);
	str = new_str;
	return (str);
}
