#include "../../../includes/minishell.h"

static size_t	calculate_result_size(char *input, size_t dollar_pos,
										size_t var_end, char *var_value,
										int is_bracket)
{
	size_t	before_len;
	size_t	after_len;
	size_t	var_value_len;

	before_len = dollar_pos;
	var_value_len = ft_strlen(var_value);
	if (is_bracket == 1 && input[var_end] == '}')
		after_len = ft_strlen(input + var_end + 1);
	else
		after_len = ft_strlen(input + var_end);
	return (before_len + var_value_len + after_len + 1);
}

char	*build_expanded_string(char *input, size_t dollar_pos, size_t var_end,
								char *var_value, int is_bracket)
{
	char	*result;
	char	*after_pos;
	size_t	result_size;

	if (input == NULL || var_value == NULL)
		return (NULL);
	result_size = calculate_result_size(input, dollar_pos, var_end, var_value,
										is_bracket);
	result = ft_calloc(sizeof(char), result_size);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, input, dollar_pos + 1);
	ft_strlcat(result, var_value, result_size);
	if (is_bracket == 1 && input[var_end] == '}')
		after_pos = input + var_end + 1;
	else
		after_pos = input + var_end;
	ft_strlcat(result, after_pos, result_size);
	return (result);
}
