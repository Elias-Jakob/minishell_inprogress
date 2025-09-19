#include "../../../includes/minishell.h"

static int	handle_first_token(t_token *token)
{
	if (token->type == TK_PIPE)
	{
		printf("minishell: syntax error: unexpected pipe at beginning\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	handle_token_type(t_token *token, t_list *current_token)
{
	if (token->type == TK_PIPE)
	{
		if (validate_pipe_sequence(current_token) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (is_redirection_token(token))
	{
		if (validate_redirection_sequence(current_token) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	validate_token_sequence(t_list *token_list)
{
	t_list	*current;
	t_token	*token;

	if (!token_list)
		return (EXIT_SUCCESS);
	current = token_list;
	token = (t_token *)current->content;
	if (handle_first_token(token) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (current)
	{
		token = (t_token *)current->content;
		if (handle_token_type(token, current) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
