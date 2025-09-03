#include "../../includes/minishell.h"

t_token_type	scan_for_quotes(char *input, size_t *length)
{
	if (*input == '"')
	{
		while (input[*length])
		{
			(*length)++;
			if (input[*length] == '"')
			{
				(*length)++;
				return (TK_DOUBLE_QUOTE);
			}
		}
	}
	else if (*input == '\'')
	{
		while (input[*length])
		{
			(*length)++;
			if (input[*length] == '\'')
			{
				(*length)++;
				return (TK_SINGLE_QUOTE);
			}
		}
	}
	return (TK_ERROR);
}

static	int	is_char_redir(char c)
{
	return (c == '|' || c == '<' || c == '>');
}


t_token_type	scan_for_word(char *input, size_t *length)
{
	while (input[*length])
	{
		(*length)++;
		if (is_space(input[*length]) || input[*length] == '\0'
			|| is_char_redir(input[*length]))
			return (TK_WORD);
	}
	return (TK_ERROR);
}

t_token_type	scan_for_env(char *input, size_t *length)
{
	(*length)++;
	while (ft_isalpha(input[*length]))
		(*length)++;
	return (TK_ENV);
}

t_token_type	scan_for_redirect(char *input, size_t *length)
{
	if (*input == '<')
	{
		(*length)++;
		if (*(input + 1) == '<')
		{
			(*length)++;
			return (TK_HEREDOC);
		}
		return (TK_REDIRECT_IN);
	}
	if (*input == '>')
	{
		(*length)++;
		if (*(input + 1) == '>')
		{
			(*length)++;
			return (TK_APPEND_OUT);
		}
		return (TK_REDIRECT_OUT);
	}
	return (TK_ERROR);
}

t_token_type	scan_for_token_type(char *input, size_t *length)
{
	if (*input == '|')
	{
		(*length)++;
		return (TK_PIPE);
	}
	if (*input == '<' || *input == '>')
		return (scan_for_redirect(input, length));
	if (*input == '$')
		return (scan_for_env(input, length));
	if (*input == '"' || *input == '\'')
		return (scan_for_quotes(input, length));
	return (scan_for_word(input, length));
}
