#include "../../includes/minishell.h"

static int	handle_exit_status(char *input, size_t *length)
{
	if (*(input + 1) == '?')
	{
		(*length) += 2;
		return (1);
	}
	return (0);
}

static int	is_char_env_variable(char c)
{
	return (ft_isalpha(c) || c == '_' || ft_isdigit(c));
}

static void	handle_start_bracket(char *input, size_t *length, int *in_bracket)
{
	if (input[*length] == '{')
	{
		(*length)++;
		*in_bracket = 1;
	}
}

static int	handle_end_bracket(char *input, size_t *length, int *in_bracket)
{
	if (*in_bracket == 1)
	{
		if (input[*length] == '}')
		{
			(*length)++;
			return (1);
		}
		return (0);
	}
	return (1);
}

t_token_type	scan_for_env(char *input, size_t *length)
{
	int	in_bracket;

	if (handle_exit_status(input, length))
		return (TK_ENV);
	(*length)++;
	in_bracket = 0;
	handle_start_bracket(input, length, &in_bracket);
	while (is_char_env_variable(input[*length]))
		(*length)++;
	if (handle_end_bracket(input, length, &in_bracket))
		return (TK_ENV);
	return (TK_ERROR);
}
