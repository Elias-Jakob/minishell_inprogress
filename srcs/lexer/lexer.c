#include "../../includes/minishell.h"

int	lexer(char *input, t_list **token_list)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (lex_input(input, &i, token_list) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
