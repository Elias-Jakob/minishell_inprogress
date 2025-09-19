#include "../../../includes/minishell.h"

static int	is_token_type_word(t_token_type type)
{
	if (type == TK_WORD || type == TK_ENV)
		return (EXIT_SUCCESS);
	if (type == TK_SINGLE_QUOTE || type == TK_DOUBLE_QUOTE)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static int	process_current_token(t_list **token_node, t_cmd **current_cmd,
								 t_cmd **cmd_head, char **env, int exit_status)
{
	t_token	*token;

	token = get_current_token(*token_node);
	if (!token)
		return (EXIT_FAILURE);
	if (is_token_type_word(token->type) == EXIT_SUCCESS)
		return (process_word_token(token, current_cmd, cmd_head, env,
							 exit_status));
	else if (token->type == TK_PIPE)
		return (process_pipe_token(current_cmd));
	else if (is_redirection_token(token))
		return (process_redirection_token(token_node, current_cmd, cmd_head));
	*token_node = (*token_node)->next;
	return (EXIT_SUCCESS);
}

static int	parse_token_sequence(t_list *token_list, t_cmd **cmd_head,
								char **env, int exit_status)
{
	int		result;
	t_list	*current_token_node;
	t_cmd	*current_cmd;

	current_token_node = token_list;
	current_cmd = NULL;
	while (current_token_node)
	{
		result = process_current_token(&current_token_node, &current_cmd,
								 cmd_head, env, exit_status);
		if (result == EXIT_FAILURE)
			return (EXIT_FAILURE);
		current_token_node = advance_token_node(current_token_node);
	}
	return (EXIT_SUCCESS);
}

int	parser(t_list *token_list, t_cmd **cmd_head, char **env, int exit_status)
{
	*cmd_head = NULL;
	if (!token_list)
		return (EXIT_SUCCESS);
	if (validate_token_sequence(token_list) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (parse_token_sequence(token_list, cmd_head, env, exit_status));
}

