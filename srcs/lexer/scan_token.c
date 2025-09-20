#include "../../includes/minishell.h"



t_token_type	scan_for_token_type(char *input, size_t *length)
{
	if (*input == '|')
		return (scan_for_operators(input, length));
	if (*input == '<' || *input == '>')
		return (scan_for_redirect(input, length));
	return (scan_compound_word_token(input, length));
}
