#include "../../includes/env.h"

char	**copy_env(char **envp, unsigned int expand)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1 + expand));
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	*get_env_value(char **env, char *key, int last_exit_status)
{
	int	i;
	int	key_len;

	if (!env || !key)
		return (NULL);
	if (*key == '?')
		return (ft_itoa(last_exit_status));
	i = 0;
	key_len = ft_strlen(key);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, key_len) == 0
			&& env[i][key_len] == '=')
			return (&env[i][key_len + 1]);
		i++;
	}
	return (NULL);
}

char	**set_env_variable(char **env, char *key, char *value)
{
	if (get_env_value(env, key, 0))
		return (reset_env_variable(env, key, value));
	else
		return (set_new_env_variable(env, key, value));
	return (NULL);
}

static char	**copy_env_without_key(char **env, int env_size,
		int key_len, char *key)
{
	int		i;
	int		j;
	char	**new_env;

	new_env = malloc(sizeof(char *) * env_size);
	if (!new_env)
		return (env);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0
			&& env[i][key_len] == '=')
		{
			i++;
			continue ;
		}
		new_env[j] = ft_strdup(env[i]);
		i++;
		j++;
	}
	new_env[j] = NULL;
	free_env(env);
	env = new_env;
	return (env);
}

char	**unset_env_variable(char **env, char *key)
{
	int		found;
	int		key_len;
	int		env_size;

	if (!env || !key)
		return (env);
	key_len = ft_strlen(key);
	env_size = 0;
	found = 0;
	while (env[env_size])
	{
		if (ft_strncmp(env[env_size], key, key_len) == 0
			&& env[env_size][key_len] == '=')
			found = 1;
		env_size++;
	}
	if (found == 0)
		return (env);
	return (copy_env_without_key(env, env_size, key_len, key));
}
