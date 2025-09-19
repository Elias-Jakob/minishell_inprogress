#include "../../../includes/minishell.h"

int	validate_redirection_sequence(t_list *token_node)
{
	t_token	*next_token;

	next_token = get_next_token(token_node);
	if (next_token == NULL)
	{
		printf("minishell: syntax error: expected filename after redirection\n");
		return (EXIT_FAILURE);
	}
	if (is_redirection_token(next_token) || next_token->type == TK_PIPE)
	{
		printf("minishell: syntax error: unexpected token after redirection\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	validate_pipe_sequence(t_list *token_node)
{
	t_token	*next_token;

	next_token = get_next_token(token_node);
	if (next_token == NULL)
	{
		printf("minishell: syntax error: unexpected end of input after pipe\n");
		return (EXIT_FAILURE);
	}
	if (next_token->type == TK_PIPE)
	{
		printf("minishell: syntax error: unexpected pipe after pipe\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

