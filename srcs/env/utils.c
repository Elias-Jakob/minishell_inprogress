#include "../../includes/env.h"

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

char	**set_new_env_variable(char **env, char *key, char *value)
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

char	**reset_env_variable(char **env, char *key, char *value)
{
	int		i;
	int		key_length;
	char	*key_value;

	i = 0;
	key_length = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_length) == 0
			&& env[i][key_length] == '=')
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (env);
	key_value = ft_calloc(sizeof(char), key_length + ft_strlen(value) + 2);
	ft_strlcat(key_value, key, key_length + 1);
	ft_strlcat(key_value, "=", key_length + 2);
	ft_strlcat(key_value, value, key_length + ft_strlen(value) + 2);
	free(env[i]);
	env[i] = key_value;
	return (env);
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
