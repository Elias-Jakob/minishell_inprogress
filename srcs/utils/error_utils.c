#include "../../includes/minishell.h"

void	fatal_error(t_exec_context *exec_context, char *msg)
{
	clean_up_commands(exec_context);
	free(exec_context->prompt);
	perror(msg);
	exit(1);
}

void	error_and_exit(char *err_msg, int exit_status)
{
	// TODO: do clean up
	perror(err_msg);
	exit(exit_status);
}
