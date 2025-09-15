#include "../../includes/minishell.h"
#include <stddef.h>

static t_token	*create_token(t_token_type type, char *input, size_t length)
{
	t_token	*token;
	char	*value_start;
	size_t	value_length;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (type == TK_DOUBLE_QUOTE && length > 2)
	{
		value_start = input + 1;
		value_length = length - 2;
		token->value = ft_strndup(value_start, value_length);
	}
	else
		token->value = ft_strndup(input, length);
	return (token);
}

static int	lex_input(char *input, size_t *i, t_list **token_list, char **env)
{
	size_t			length;
	t_token_type	type;
	t_token			*token;
	t_list			*new_tok;

	length = 0;
	if (!is_space(input[*i]))
	{
		type = scan_for_token_type(input + *i, &length, env);
		if (type == TK_ERROR)
		{
			printf("minishell: syntax error near position %zu\n", *i);
			return (EXIT_FAILURE);
		}
		token = create_token(type, input + *i, length);
		if (!token)
			return (EXIT_FAILURE);
		new_tok = ft_lstnew((void *)token);
		if (!new_tok)
		{
			free(token->value);
			free(token);
			return (EXIT_FAILURE);
		}
		ft_lstadd_back(token_list, new_tok);
	}
	else
		length++;
	*i += length;
	return (EXIT_SUCCESS);
}

int	lexer(char *input, t_list **token_list, char **env)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (lex_input(input, &i, token_list, env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
