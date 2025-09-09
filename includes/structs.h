#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdlib.h>
# include "enums.h"

typedef struct	s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_redirs
{
	t_redirs_type	in_type;
	t_redirs_type	out_type;
	char					*infile_name;
	char					*outfile_name;
	char					*heredoc_delimiter;  // NEW: for << operator
	char					*heredoc_content;    // NEW: store heredoc content
	int						fds[2];
	int						append_mode;         // for >>
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

typedef struct s_exec_context
{
	char				**envp;
	char				*paths;
	char				*prompt;
	t_cmd				*commands;
	int					exit_status;
	int					stdin_backup;       // NEW: to restore stdin after redirections
	int					stdout_backup;      // NEW: to restore stdout after redirections
}   t_exec_context;

#endif
