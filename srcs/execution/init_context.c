#include "../../includes/minishell.h"

static char	**copy_envp(char **envp)
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

void	init_exec(t_exec_context *exec_context, char **envp)
{
	exec_context->paths = getenv("PATH");
	exec_context->envp = copy_envp(envp);
	if (!exec_context->envp)
		exit(1);
}
