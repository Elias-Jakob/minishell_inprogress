#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
		char			*line;
		t_exec_context	exec_context;

		(void)argc;
		(void)argv;
		exec_context.envp = envp;
		exec_context.paths = getenv("PATH");
		using_history();
		stifle_history(15);
		while ((line = readline("$> ")) != NULL)
		{
				printf("%s\n", line);
				add_history(line);
				free(line);
		}
		clear_history();
		return (EXIT_SUCCESS);
}
