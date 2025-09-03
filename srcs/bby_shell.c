#include "../includes/minishell.h"

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

// int	main(int argc, char **argv, char **envp)
// {
// 	char			*line;
// 	t_exec_context	exec_context;
// 	t_list			*token_list;
// 	t_cmd			*cmd_head;
//
// 	(void)argc;
// 	(void)argv;
// 	exec_context.envp = envp;
// 	exec_context.paths = getenv("PATH");
// 	(void)exec_context;
// 	token_list = ft_lstnew(NULL);
// 	token_list = NULL;
// 	cmd_head = NULL;
// 	line = readline("$> ");
// 	while (line != NULL && ft_strncmp("exit", line, 4))
// 	{
// 		token_list = NULL;
// 		cmd_head = NULL;
// 		if (lexer(line, &token_list))
// 			return (EXIT_FAILURE);
// 		parser(token_list, &cmd_head);
// 		// debug_lexer(token_list, line);
// 		// debug_parser(cmd_head, line);
// 		ft_lstclear(&token_list, free_token);
// 		// leberton: Hmmmmmm so it is my fault not yours if I understand it correctly... My bad :D
// 		exec_context.commands = cmd_head;
// 		exec_command_list(&exec_context);
// 		clean_up_commands(&exec_context);
// 		add_history(line);
// 		free(line);
// 		token_list = NULL;
// 		cmd_head = NULL;
// 		line = readline("$> ");
// 		// write(1, "\n", 1);
// 		// rl_on_new_line();
// 		// rl_replace_line("", 0);
// 		// rl_redisplay();
// 	}
// 	clear_history();
// 	return (EXIT_SUCCESS);
// }

// For lexer/parser
int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_list			*token_list;
	t_cmd			*cmd_head;

	(void)argc;
	(void)argv;
	(void)envp;
	token_list = ft_lstnew(NULL);
	token_list = NULL;
	cmd_head = NULL;
	line = readline("$> ");
	while (line != NULL && ft_strncmp("exit", line, 4))
	{
		token_list = NULL;
		cmd_head = NULL;
		if (lexer(line, &token_list))
			return (EXIT_FAILURE);
		parser(token_list, &cmd_head);
		debug_lexer(token_list, line);
		debug_parser(cmd_head, line);
		ft_lstclear(&token_list, free_token);
		add_history(line);
		free(line);
		token_list = NULL;
		cmd_head = NULL;
		line = readline("$> ");
	}
	clear_history();
	return (EXIT_SUCCESS);
}

