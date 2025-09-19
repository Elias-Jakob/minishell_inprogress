#include "../../../includes/minishell.h"

char	*expand_env_var(char *input, size_t dollar_pos, char **env, int exit_status)
{
	char	*var_name;
	char	*var_value;
	char	*result;
	size_t	var_end;
	int		is_bracket;

	if (input == NULL)
		return (NULL);
	var_end = find_variable_end(input, dollar_pos, &is_bracket);
	var_name = extract_variable_name(input, dollar_pos, var_end, is_bracket);
	if (var_name == NULL)
		return (NULL);
	var_value = resolve_variable_value(var_name, env, exit_status);
	if (var_value == NULL)
	{
		free(var_name);
		return (NULL);
	}
	result = build_expanded_string(input, dollar_pos, var_end, var_value, is_bracket);
	cleanup_variable_memory(var_name, var_value);
	return (result);
}
