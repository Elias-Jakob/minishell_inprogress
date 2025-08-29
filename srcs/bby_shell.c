#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	// char						*line;
	t_exec_context	exec_context;
	t_pipeline			pipeline;
	t_cmd						test_cmd;
	t_redirs				cmd_redirs;

	(void)argc;
	(void)argv;
	exec_context.envp = envp;
	exec_context.paths = getenv("PATH");
	cmd_redirs.outfile_name = ft_strdup("outfile.txt");
	cmd_redirs.is_heredoc = 0;
	cmd_redirs.append_mode = 0;
	test_cmd.argv = ft_split("cat Makefile", ' ');
	test_cmd.is_builtin = 0;
	test_cmd.redirs = &cmd_redirs;
	test_cmd.next = NULL;
	pipeline.commands = &test_cmd;
	run_pipline(pipeline);

	// using_history();
	// stifle_history(15);
	// while ((line = readline("$> ")) != NULL)
	// {
	// 		printf("%s\n", line);
	// 		add_history(line);
	// 		free(line);
	// }
	// clear_history();
	return (EXIT_SUCCESS);
}
