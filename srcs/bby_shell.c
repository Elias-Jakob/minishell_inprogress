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
	t_cmd						test_cmd2;
	t_cmd						test_cmd3;
	t_redirs				cmd_redirs;
	t_redirs				cmd_redirs2;
	t_redirs				cmd_redirs3;

	(void)argc;
	(void)argv;
	exec_context.envp = envp;
	exec_context.paths = getenv("PATH");
	exec_context.prompt = NULL;

	// cat example
	cmd_redirs2.infile_name = NULL;
	cmd_redirs2.outfile_name = ft_strdup("outfile.txt");
	cmd_redirs2.in_type = RD_PIPE;
	cmd_redirs2.out_type = RD_FILE;
	cmd_redirs2.fds[0] = STDIN_FILENO;
	cmd_redirs2.fds[1] = STDOUT_FILENO;
	test_cmd2.argv = ft_split("wc", ' ');
	test_cmd2.is_builtin = 0;
	test_cmd2.redirs = &cmd_redirs2;
	test_cmd2.next = NULL;

// ls example
	cmd_redirs3.infile_name = NULL;
	cmd_redirs3.outfile_name = NULL;
	cmd_redirs3.in_type = RD_PIPE;
	cmd_redirs3.out_type = RD_PIPE;
	cmd_redirs3.fds[0] = STDIN_FILENO;
	cmd_redirs3.fds[1] = STDOUT_FILENO;
	test_cmd3.argv = ft_split("cat", ' ');
	test_cmd3.is_builtin = 0;
	test_cmd3.redirs = &cmd_redirs3;
	test_cmd3.next = &test_cmd2;


	cmd_redirs.infile_name = ft_strdup("big_text.txt");
	cmd_redirs.outfile_name = NULL;
	cmd_redirs.in_type = RD_FILE;
	cmd_redirs.out_type = RD_PIPE;
	cmd_redirs.fds[0] = STDIN_FILENO;
	cmd_redirs.fds[1] = STDOUT_FILENO;
	test_cmd.argv = ft_split("cat", ' ');
	test_cmd.is_builtin = 0;
	test_cmd.redirs = &cmd_redirs;
	test_cmd.next = &test_cmd3;

	pipeline.commands = &test_cmd;
	exec_context.pipeline = &pipeline;
	run_pipeline(&exec_context);
	return (EXIT_SUCCESS);
}
