#include "../../../includes/minishell.h"

size_t	find_variable_end(char *input, size_t dollar_pos, int *is_bracket)
{
	size_t	i;

	i = dollar_pos + 1;
	*is_bracket = 0;
	if (input[i] == '?')
		return (dollar_pos + 2);
	if (input[i] == '{')
	{
		i++;
		*is_bracket = 1;
	}
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
	return (i);
}

char	*extract_variable_name(char *input, size_t dollar_pos, size_t var_end,
							int	is_bracket)
{
	size_t	start;
	size_t	len;

	start = dollar_pos + 1;
	if (is_bracket == 1)
		start++;
	len = var_end - start;
	if (is_bracket && input[var_end] == '}')
		len--;
	return (ft_substr(input, start, len));
}
