#include "../../includes/minishell.h"

t_token_type	scan_for_single_quotes(char *input, size_t *length)
{
	(*length)++;
	while (input[*length] && input[*length] != '\'')
		(*length)++;
	if (input[*length] != '\'')
		return (TK_ERROR);
	(*length)++;
	return (TK_SINGLE_QUOTE);
}

t_token_type	scan_for_double_quotes(char *input, size_t *length)
{
	(*length)++;
	while (input[*length] && input[*length] != '"')
		(*length)++;
	if (input[*length] != '"')
		return (TK_ERROR);
	(*length)++;
	return (TK_DOUBLE_QUOTE);
}

t_token_type	scan_for_quotes(char *input, size_t *length)
{
	if (*input == '"')
		return (scan_for_double_quotes(input, length));
	else if (*input == '\'')
		return (scan_for_single_quotes(input, length));
	return (TK_ERROR);
}

