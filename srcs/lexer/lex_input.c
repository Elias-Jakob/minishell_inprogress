#include "../../includes/minishell.h"
#include <stdlib.h>

static int	handle_whitespaces(char *input, size_t *i, size_t *length)
{
	if (is_space(input[*i]))
	{
		(*length)++;
		return (1);
	}
	return (0);
}

static int	scan_and_validate_token(char *input, size_t *i, size_t *length,
								   t_token_type *type)
{
	*type = scan_for_token_type(input + *i, length);
	if (*type == TK_ERROR)
	{
		printf("minishell: syntax error near position %ld\n", *i);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	create_and_add_token(char *input, size_t i, size_t length,
								t_token_type type, t_list **token_list)
{
	t_token	*token;
	t_list	*new_token;

	token = create_token(type, input + i, length);
	if (token == NULL)
		return (EXIT_FAILURE);
	new_token = ft_lstnew((void *)token);
	if (new_token == NULL)
	{
		destroy_token(token);
		return (EXIT_FAILURE);
	}
	ft_lstadd_back(token_list, new_token);
	return (EXIT_SUCCESS);
}

int	lex_input(char *input, size_t *i, t_list **token_list)
{
	size_t			length;
	t_token_type	type;

	length = 0;
	if (handle_whitespaces(input, i, &length) == 1)
	{
		*i += length;
		return (EXIT_SUCCESS);
	}
	if (scan_and_validate_token(input, i, &length, &type) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_and_add_token(input, *i, length, type, token_list) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*i += length;
	return (EXIT_SUCCESS);
}
