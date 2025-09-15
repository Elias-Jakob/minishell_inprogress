#include "../../includes/minishell.h"

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

size_t	str_arr_len(char **arr)
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

static char	**alloc_new_env(t_exec_context *exec_context, int new_size)
{
	char	**new_envp;
	size_t	len;

	len = str_arr_len(exec_context->envp);
	new_envp = (char **)malloc(sizeof(char *) * (len + new_size));
	if (!new_envp)
		perror("env_name_add: malloc failed");
	return (new_envp);
}

// 1. gets *name
// 2. create new name
//		- if that fails let everything un touched
// 3. free *name
// 4. set *name to new name
void	env_value_update(char **name, char *new_name)
{
	free(*name);
	*name = new_name;
}

// 1. alloc for envp + 1 for new element
// 2. copy envp into the new alloced envp
// 3. last element gets to be new element
// 4. free_str_arr the old envp
int	env_name_add(t_exec_context *exec_context, char *new_name)
{
	size_t	i;
	char	**new_envp;

	new_envp = alloc_new_env(exec_context, 2);
	if (!new_envp)
		return (0);
	i = 0;
	while (exec_context->envp[i])
	{
		new_envp[i] = ft_strdup(exec_context->envp[i]);
		if (!new_envp[i])
			return (free_str_arr(new_envp),
			perror("env_name_add: ft_strdup failed"), 0);
		i++;
	}
	new_envp[i++] = new_name;
	new_envp[i] = NULL;
	free_str_arr(exec_context->envp);
	exec_context->envp = new_envp;
	return (1);
}

static int	is_env_name(char *env_name, char *name, size_t name_len)
{
	size_t	env_name_len;

	if (ft_strncmp(env_name, name, name_len))
		return (0);
	env_name_len = ft_strlen(env_name);
	if (name_len < env_name_len && env_name[name_len] != '=')
		return (0);
	return (1);
}

// 1. gets *name
// 2. alloc for envp - 1
// 3. copy everything from envp over to alloc if envp[i] != name
// 4. free_str_arr the old envp
int	env_name_remove(t_exec_context *exec_context, char *name)
{
	size_t	i;
	char	**new_envp;
	size_t	name_len;
	size_t	new_i;

	new_envp = alloc_new_env(exec_context, 0);
	if (!new_envp)
		return (0);
	i = 0;
	new_i = 0;
	name_len = ft_strlen(name);
	while (exec_context->envp[i])
	{
		if (!is_env_name(exec_context->envp[i], name, name_len))
		{
			new_envp[new_i] = ft_strdup(exec_context->envp[i]);
			if (!new_envp[new_i++])
				return (free_str_arr(new_envp),
				perror("env_name_remove: ft_strdup failed"), 0);
		}
		i++;
	}
	new_envp[i] = NULL;
	free_str_arr(exec_context->envp);
	exec_context->envp = new_envp;
	return (1);
}
// refactore this func
