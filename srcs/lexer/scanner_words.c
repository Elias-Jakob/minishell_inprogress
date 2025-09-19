#include "../../includes/minishell.h"

static int	is_word_delimiter(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int	is_char_word(char c)
{
	return (is_space(c) || c == '\0' || is_word_delimiter(c));
}

t_token_type	scan_for_word(char *input, size_t *length)
{
	while (input[*length])
	{
		(*length)++;
		if (is_char_word(input[*length]))
			return (TK_WORD);
	}
	return (TK_ERROR);
}
