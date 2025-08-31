#include "../../includes/minishell.h"

typedef struct s_redirs
{
	t_redirs_type	in_type;
	t_redirs_type	out_type;
	char					*infile_name;
	char					*outfile_name;
	char					*heredoc_delimiter;  // NEW: for << operator
	char					*heredoc_content;    // NEW: store heredoc content
	int						fds[2];
}	t_redirs;

// Fix s_cmd - missing struct keyword
typedef struct s_cmd
{
	char						**argv;
	t_redirs				*redirs;
	pid_t						pid;        // use pid_t instead of t_pid
	int							is_builtin;
	int							exit_status;
	struct s_cmd		*next;      // need 'struct' keyword
}   t_cmd;



void	clean_up_pipeline(t_pipeline *pipeline)
{
	// free all allocations
	// close all fds
	
}

void	fatal_error(t_exec_context *exec_context, char *msg)
{
	clean_up_pipeline(exec_context->pipeline);
	free(exec_context->prompt);
	free(exec_context->paths);
	perror(msg);
	exit(1);
}

void	error_and_exit(char *err_msg, int exit_status)
{
	// TODO: do clean up
	perror(err_msg);
	exit(exit_status);
}
