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
	t_list			*token_list;
	t_cmd			*cmd_head;
	t_exec_context	exec_context;

	(void)argc;
	(void)argv;
	token_list = ft_lstnew(NULL);
	token_list = NULL;
	cmd_head = NULL;
	exec_context.envp = envp;
	exec_context.paths = getenv("PATH");
	exec_context.prompt = readline("$> ");
	while (exec_context.prompt != NULL)
	{
		token_list = NULL;
		cmd_head = NULL;
		if (lexer(exec_context.prompt, &token_list))
			return (EXIT_FAILURE);
		parser(token_list, &cmd_head);
		debug_lexer(token_list, exec_context.prompt);
		debug_parser(cmd_head, exec_context.prompt);
		ft_lstclear(&token_list, free_token);
		// leberton: Hmmmmmm so it is my fault not yours if I understand it correctly... My bad :D
		// ejakob: ejakob makes no mistakes hahah!!! ps. thx for the excellent fix:)
		// leberton: Never ? Are you sure ? Didn't I see some SEGV's on your screen the other day ? And what fix x) ?
		// leberton: I like very much all the builtins that are working :))
		// ejakob: I changed one or two things around here... i hope thats ok. Also, i checked the subject again
		//         and i noticed that i was doing way too much stuff in cd - we only need to implement absolute and relative paths :0 RTFM!
		exec_context.commands = cmd_head;
		exec_command_list(&exec_context);
		clean_up_commands(&exec_context);
		// TODO: only break if prompt is exit [n]; not break if exit is in a pipeline
		if (!ft_strncmp("exit", exec_context.prompt, 4))
			break ;
		printf("%d ", exec_context.exit_status);
		//
		//
		//
		//
		// sleep(10);
		// fix_quotes();
		add_history(exec_context.prompt);
		free(exec_context.prompt);
		token_list = NULL;
		cmd_head = NULL;
		exec_context.prompt = readline("$> ");
	}
	clear_history();
	free(exec_context.prompt);
	return (exec_context.exit_status);
}

