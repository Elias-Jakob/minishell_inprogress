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
		t_list			*cmd_list;


		(void)argc;
		(void)argv;
		(void)print_token;
		exec_context.envp = envp;
		exec_context.paths = getenv("PATH");
		token_list = ft_lstnew(NULL);
		// using_history();
		// stifle_history(3);
		token_list = NULL;
		cmd_list = NULL;
		while ((line = readline("$> ")) != NULL)
		{
				token_list = NULL;
				cmd_list = NULL;
				if (lexer(line, &token_list))
						return (EXIT_FAILURE);
				if (parser(token_list, &cmd_list))
					return (EXIT_FAILURE);
				if (!cmd_list) {
					add_history(line);
					free(line);
					continue;
				}
				t_list	*curr_lst = cmd_list;
				t_cmd	*curr_cmd;
				while (curr_lst)
				{
						curr_cmd = (t_cmd *)curr_lst->content;
						printf("COMMAND: %s\n", curr_cmd->argv && curr_cmd->argv[0] ? curr_cmd->argv[0] : "(null)");
						for (int i = 0; curr_cmd->argv[i]; i++)
							printf("ARG: %s\n", curr_cmd->argv[i]);
						curr_lst = curr_lst->next;
				}
				add_history(line);
				free(line);
				ft_lstclear(&token_list, free_token);
				ft_lstclear(&cmd_list, free_cmd);
				token_list = NULL;
				cmd_list = NULL;
		}
		clear_history();
		return (EXIT_SUCCESS);
	// char						*line;
	// t_exec_context	exec_context;
	// t_pipeline			pipeline;
	// t_cmd						test_cmd;
	// t_redirs				cmd_redirs;
	//
	// (void)argc;
	// (void)argv;
	// exec_context.envp = envp;
	// exec_context.paths = getenv("PATH");
	// cmd_redirs.outfile_name = ft_strdup("outfile.txt");
	// cmd_redirs.is_heredoc = 0;
	// cmd_redirs.append_mode = 0;
	// test_cmd.argv = ft_split("cat Makefile", ' ');
	// test_cmd.is_builtin = 0;
	// test_cmd.redirs = &cmd_redirs;
	// test_cmd.next = NULL;
	// pipeline.commands = &test_cmd;
	// run_pipline(pipeline);
}
