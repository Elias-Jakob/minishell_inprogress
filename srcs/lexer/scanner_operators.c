#include "../../includes/minishell.h"

t_token_type	scan_for_operators(char *input, size_t *length)
{
	if (*input == '|')
	{
		(*length)++;
		return (TK_PIPE);
	}
	return (TK_ERROR);
}
