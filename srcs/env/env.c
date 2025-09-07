#include "../../includes/libft.h"

void	free_env(char **env)
{
	int	i;

	i = 0;
	while(env[i])
		free(env[i++]);
	free(env);
}

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

char	*get_env_value(char **env, char *key)
{
	int	i;
	int	key_len;

	if (!env || !key)
		return (NULL);
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

static char	**reset_env_variable(char **env, char *key, char *value);
static char	**set_new_env_variable(char **env, char *key, char *value);

char	**set_env_variable(char **env, char *key, char *value)
{
	if (get_env_value(env, key))
		return (reset_env_variable(env, key, value));
	else
		return (set_new_env_variable(env, key, value));
	return (NULL);
}

static char	**reset_env_variable(char **env, char *key, char *value)
{
	int		i;
	int		found;
	int		key_length;
	char	*key_value;

	i = 0;
	found = 0;
	key_length = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_length) == 0
			&& env[i][key_length] == '=')
		{
			found = 1;
			break;
		}
		i++;
	}
	if (found == 0)
		return (env);
	key_value = ft_calloc(sizeof(char), key_length + ft_strlen(value) + 2);
	ft_strlcat(key_value, key, key_length + 1);
	ft_strlcat(key_value, "=", key_length + 2);
	ft_strlcat(key_value, value, key_length + ft_strlen(value) + 2);
	free(env[i]);
	env[i] = key_value;
	return (env);
}

static char	**set_new_env_variable(char **env, char *key, char *value)
{
	int		i;
	char	**new_env;
	char	*key_value;

	i = 0;
	new_env = copy_env(env, 1);
	while (new_env[i])
		i++;
	key_value = ft_calloc(sizeof(char), ft_strlen(key) + ft_strlen(value) + 2);
	ft_strlcat(key_value, key, ft_strlen(key) + 1);
	ft_strlcat(key_value, "=", ft_strlen(key) + 2);
	ft_strlcat(key_value, value, ft_strlen(key) + ft_strlen(value) + 2);
	new_env[i] = key_value;
	new_env[i + 1] = NULL;
	free_env(env);
	env = new_env;
	return (new_env);
}

char	**unset_env_variable(char **env, char *key)
{
	int		i;
	int		j;
	int		found;
	int		key_len;
	int		env_size;
	char	**new_env;

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
			continue;
		}
		new_env[j] = ft_strdup(env[i]);
		i++;
		j++;
	}
	new_env[j] = NULL;
	free_env(env);
	return (new_env);
}

char	*expand_variables(char *str, char **env)
{
	char	*new_str;

	new_str = get_env_value(env, str);
	if (new_str == NULL)
		return (str);
	str = new_str;
	return (str);
}
