#include "../../includes/minishell.h"

static int	is_char_redirect_in(char c)
{
	return (c == '<');
}

static int	is_char_redirect_out(char c)
{
	return (c == '>');
}

static t_token_type	handle_redirect_in(char *input, size_t *length)
{
	(*length)++;
	if (*(input + 1) == '<')
	{
		(*length)++;
		return (TK_HEREDOC);
	}
	return (TK_REDIRECT_IN);
}

static t_token_type	handle_redirect_out(char *input, size_t *length)
{
	(*length)++;
	if (*(input + 1) == '>')
	{
		(*length)++;
		return (TK_APPEND_OUT);
	}
	return (TK_REDIRECT_OUT);
}

t_token_type	scan_for_redirect(char *input, size_t *length)
{
	if (is_char_redirect_in(*input))
		return (handle_redirect_in(input, length));
	if (is_char_redirect_out(*input))
		return (handle_redirect_out(input, length));
	return (TK_ERROR);
}
