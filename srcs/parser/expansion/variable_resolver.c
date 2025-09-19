#include "../../../includes/minishell.h"

char	*resolve_variable_value(char *var_name, char **env, int exit_status)
{
	char	*var_value;

	if (var_name == NULL)
		return (ft_strdup(""));
	if (ft_strncmp(var_name, "?", 1) == 0)
		return (ft_itoa(exit_status));
	var_value = get_env_value(env, var_name);
	if (var_value == NULL)
		return (ft_strdup(""));
	return (ft_strdup(var_value));
}

void	cleanup_variable_memory(char *var_name, char *var_value)
{
	if (var_name)
		free(var_name);
	if (var_value)
		free(var_value);
}

int	needs_special_cleanup(char *var_name)
{
	if (var_name == NULL)
		return (0);
	return (ft_strncmp(var_name, "?", 1) == 0);
}
