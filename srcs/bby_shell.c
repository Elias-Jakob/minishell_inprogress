#include "../includes/minishell.h"

/*
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
*/

int	main(int argc, char **argv, char **envp)
{
		// char			*line;
		// t_exec_context	exec_context;
		// t_list			*token_list;
		//
		//
		// (void)argc;
		// (void)argv;
		// exec_context.envp = envp;
		// exec_context.paths = getenv("PATH");
		// token_list = ft_lstnew(NULL);
		// // using_history();
		// // stifle_history(3);
		// while ((line = readline("$> ")) != NULL)
		// {
		// 		if (lexer(line, &token_list))
		// 				return (EXIT_FAILURE);
		// 		while (token_list)
		// 		{
		// 				print_token((t_token *)token_list->content);
		// 				token_list = token_list->next;
		// 		}
		// 		add_history(line);
		// 		free(line);
		// }
		// clear_history();
		// return (EXIT_SUCCESS);
	// char						*line;
	t_exec_context	exec_context;
	t_pipeline			pipeline;
	t_cmd						test_cmd;
	t_redirs				cmd_redirs;

	(void)argc;
	(void)argv;
	exec_context.envp = envp;
	exec_context.paths = getenv("PATH");
	// ls example
	// cmd_redirs.infile_name = NULL;
	// cmd_redirs.outfile_name = ft_strdup("outfile.txt");
	// cmd_redirs.type = RD_FILE;
	// cmd_redirs.append_mode = 0;
	// test_cmd.argv = ft_split("ls", ' ');
	// test_cmd.is_builtin = 0;
	// test_cmd.redirs = &cmd_redirs;
	// test_cmd.next = NULL;
	// pipeline.commands = &test_cmd;

	// cat example
	cmd_redirs.infile_name = ft_strdup("infile");
	cmd_redirs.outfile_name = ft_strdup("outfile.txt");
	cmd_redirs.type = RD_FILE;
	cmd_redirs.fds[0] = STDIN_FILENO;
	cmd_redirs.fds[1] = STDOUT_FILENO;
	test_cmd.argv = ft_split("cat -e", ' ');
	test_cmd.is_builtin = 0;
	test_cmd.redirs = &cmd_redirs;
	test_cmd.next = NULL;
	pipeline.commands = &test_cmd;
	// pipeline.cmd_count = 1;
	// pipeline.pids = (int *)malloc(sizeof(int) * pipeline.cmd_count);
	// if (!pipeline.pids)
	// 	exit_and_error("malloc failed", 1);
	run_pipeline(&pipeline, &exec_context);
	return (EXIT_SUCCESS);
}
