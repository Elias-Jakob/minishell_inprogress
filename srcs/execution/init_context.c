#include "../../includes/minishell.h"

static size_t	str_arr_len(char **arr)
{
	size_t	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

static char	**copy_envp(char **envp)
{
	char	**alloc_envp;
	size_t	arr_len;
	size_t	i;

	arr_len = str_arr_len(envp);
	alloc_envp = (char **)malloc(sizeof(char *) * (arr_len + 1));
	if (!alloc_envp)
		return (perror("init_envp: malloc failed"), NULL);
	i = 0;
	while (i < arr_len)
	{
		alloc_envp[i] = ft_strdup(envp[i]);
		if (!alloc_envp[i])
			// WARNING: passing uninitialised stuff here to free_str_arr
			return (free_str_arr(alloc_envp),
			perror("init_envp: ft_strdup failed"), NULL);
		i++;
	}
	alloc_envp[i] = NULL;
	return (alloc_envp);
}

void	init_exec(t_exec_context *exec_context, char **envp)
{
	exec_context->paths = getenv("PATH");
	exec_context->envp = copy_envp(envp);
	if (!exec_context->envp)
		exit(1);
}
