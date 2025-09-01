#include "../../includes/minishell.h"

static t_token	*create_token(t_token_type type, char *input, size_t length)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strndup(input, length);
	return (token);
}

static void	lex_input(char *input, size_t *i, t_list **token_list)
{
	size_t			length;
	t_token_type	type;
	t_token			*token;
	t_list			*new_tok;

	length = 0;
	if (!is_space(input[*i]))
	{
		type = scan_for_token_type(input + *i, &length);
		if (type == TK_ERROR)
		{
			printf("Error: Scanning for token type\n");
			token = NULL;
		}
		else
		{
			token = create_token(type, input + *i, length);
			new_tok = ft_lstnew((void *)token);
			ft_lstadd_back(token_list, new_tok);
		}
	}
	else
		length++;
	*i += length;
}

int	lexer(char *input, t_list **token_list)
{
	size_t	i;

	i = 0;
	while (input[i])
		lex_input(input, &i, token_list);
	return (EXIT_SUCCESS);
}
