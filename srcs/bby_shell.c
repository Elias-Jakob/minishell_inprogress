#include "../includes/minishell.h"

static char	*token_type_to_str(t_token_type type)
{
		if (type == TK_WORD)
				return ("WORD");
		if (type == TK_PIPE)
				return ("PIPE");
		if (type == TK_REDIRECT_IN)
				return ("TK_REDIRECT_IN");
		if (type == TK_REDIRECT_OUT)
				return ("TK_REDIRECT_OUT");
		if (type == TK_APPEND_OUT)
				return ("TK_APPEND_OUT");
		if (type == TK_HEREDOC)
				return ("TK_HEREDOC");
		if (type == TK_ENV)
				return ("TK_ENV");
		if (type == TK_SINGLE_QUOTE)
				return ("TK_SINGLE_QUOTE");
		if (type == TK_DOUBLE_QUOTE)
				return ("TK_DOUBLE_QUOTE");
		if (type == TK_ERROR)
				return ("TK_ERROR");
		return ("Uknown token...");
}

static void	print_token(t_token *token)
{
		if (token)
				printf("Type: %s\nValue: %s\n", token_type_to_str(token->type), token->value);
}

void free_token(void *content)
{
    t_token *token = (t_token *)content;
    if (!token)
        return;
    if (token->value)
        free(token->value);
    free(token);
}

void free_cmd(void *content)
{
    t_cmd *cmd = (t_cmd *)content;
    if (!cmd)
        return;
    if (cmd->argv)
    {
        for (int i = 0; cmd->argv[i]; i++)
            free(cmd->argv[i]);
        free(cmd->argv);
    }
    free(cmd);
}

int	main(int argc, char **argv, char **envp)
{
		char			*line;
		t_exec_context	exec_context;
		t_list			*token_list;
		t_cmd			*cmd_head;


		(void)argc;
		(void)argv;
		(void)print_token;
		exec_context.envp = envp;
		exec_context.paths = getenv("PATH");
		token_list = ft_lstnew(NULL);
		// using_history();
		// stifle_history(3); trouve et lance la commande.
		token_list = NULL;
		cmd_head = NULL;
		while ((line = readline("$> ")) != NULL)
		{
				token_list = NULL;
				cmd_head = NULL;
				if (lexer(line, &token_list))
						return (EXIT_FAILURE);
				if (parser(token_list, &cmd_head))
					return (EXIT_FAILURE);
				if (!cmd_head) {
					add_history(line);
					free(line);
					continue;
				}
				t_cmd	*cmd = cmd_head;
				while (cmd)
				{
						printf("COMMAND: %s\n", cmd->argv && cmd->argv[0] ? cmd->argv[0] : "(null)");
						for (int i = 0; cmd->argv[i]; i++)
							printf("ARG: %s\n", cmd->argv[i]);
						if (cmd->redirs)
						{
							printf("OUT REDIR = %d\n", cmd->redirs->out_type);
							printf("IN REDIR = %d\n", cmd->redirs->in_type);
						}
						cmd = cmd->next;
				}
				add_history(line);
				free(line);
				ft_lstclear(&token_list, free_token);
				token_list = NULL;
				cmd_head = NULL;
		}
		clear_history();
		return (EXIT_SUCCESS);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char			*line;
// 	t_exec_context	exec_context;
// 	t_list			*token_list;
//
//
// 	(void)argc;
// 	(void)argv;
// 	exec_context.envp = envp;
// 	exec_context.paths = getenv("PATH");
// 	token_list = ft_lstnew(NULL);
// 	// using_history();
// 	// stifle_history(3);
// 	while ((line = readline("$> ")) != NULL)
// 	{
// 		if (lexer(line, &token_list))
// 			return (EXIT_FAILURE);
// 		while (token_list)
// 		{
// 			print_token((t_token *)token_list->content);
// 			token_list = token_list->next;
// 		}
// 		add_history(line);
// 		free(line);
// 	}
// 	clear_history();
// 	return (EXIT_SUCCESS);
// 	return (EXIT_SUCCESS);
// }
