#include "../../includes/minishell.h"

int	scan_env_component(char *input, size_t *pos)
{
	size_t	temp_len;

	temp_len = 0;
	if (scan_for_env(input + *pos, &temp_len) == TK_ERROR)
		return (0);
	*pos += temp_len;
	return (1);
}

int	scan_quote_component(char *input, size_t *pos)
{
	size_t	temp_len;

	temp_len = 0;
	if (scan_for_quotes(input + *pos, &temp_len) == TK_ERROR)
		return (0);
	*pos += temp_len;
	return (1);
}

void	scan_text_component(char *input, size_t *pos)
{
	while (input[*pos] && !is_token_boundary(input[*pos])
		&& input[*pos] != '$' && input[*pos] != '"' && input[*pos] != '\'')
		(*pos)++;
}