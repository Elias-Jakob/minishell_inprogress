#include "../../includes/minishell.h"

static int	scan_next_component(char *input, size_t *pos)
{
	if (input[*pos] == '$')
		return (scan_env_component(input, pos));
	else if (input[*pos] == '"' || input[*pos] == '\'')
		return (scan_quote_component(input, pos));
	else
	{
		scan_text_component(input, pos);
		return (1);
	}
}

t_token_type	scan_compound_word_token(char *input, size_t *length)
{
	size_t	pos;

	pos = 0;
	while (input[pos] && !is_token_boundary(input[pos]))
	{
		if (!scan_next_component(input, &pos))
			return (TK_ERROR);
	}
	*length = pos;
	if (pos == 0)
		return (TK_ERROR);
	return (TK_WORD);
}