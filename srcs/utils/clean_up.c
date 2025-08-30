#include "../../includes/minishell.h"

void	error_and_exit(char *err_msg, int exit_status)
{
	// TODO: do clean up
	perror(err_msg);
	exit(exit_status);
}
