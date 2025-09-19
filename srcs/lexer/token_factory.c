#include "../../includes/minishell.h"

t_token	*create_token(t_token_type type, char *input, size_t length)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (type == TK_DOUBLE_QUOTE && length > 2)
		token->value = ft_strndup(input + 1, length - 2);
	else
		token->value = ft_strndup(input, length);
	return (token);
}

void	destroy_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->value == NULL)
	{
		free(token);
		return ;
	}
	free(token->value);
	free(token);
	return ;
}
