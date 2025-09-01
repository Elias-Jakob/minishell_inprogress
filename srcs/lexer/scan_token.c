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

t_token_type	scan_for_word(char *input, size_t *length)
{
	while (input[*length])
	{
		(*length)++;
		if ((!ft_isalnum(input[*length]) && *input != '-')
			|| is_space(input[*length]))
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
	if (ft_isalnum(*input) || *input == '-')
		return (scan_for_word(input, length));
	return (TK_ERROR);
}
