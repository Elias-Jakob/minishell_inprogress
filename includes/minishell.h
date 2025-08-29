#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_error
{
    ERR_NONE,
    ERR_CMD_NOT_FOUND,      // 127
    ERR_PERMISSION_DENIED,  // 126
    ERR_PIPE_FAIL,
    ERR_FORK_FAIL,
    ERR_FILE_NOT_FOUND
}   t_error;

typedef enum e_builtin
{
    BUILTIN_NONE,
    BUILTIN_CD,
    BUILTIN_ECHO,
    BUILTIN_PWD,
    BUILTIN_EXPORT,
    BUILTIN_UNSET,
    BUILTIN_ENV,
    BUILTIN_EXIT
}   t_builtin;

typedef enum e_token_type
{
		TK_WORD,
		TK_PIPE,
		TK_REDIRECT_IN,
		TK_REDIRECT_OUT,
		TK_APPEND_OUT,
		TK_SINGLE_QUOTE,
		TK_DOUBLE_QUOTE,
		TK_HEREDOC,
		TK_ENV,
		TK_ERROR
}	t_token_type;

typedef struct	s_token
{
		t_token_type	type;
		char			*value;
}	t_token;

typedef struct s_redirs
{
    char    *infile_name;
    char    *outfile_name;
    char    *heredoc_delimiter;  // NEW: for << operator
    char    *heredoc_content;    // NEW: store heredoc content
		int			fds[2];
    int     append_mode;         // for >>
		int			is_pipe;
    int     is_heredoc;          // NEW: flag to know if using heredoc
}   t_redirs;

// Fix s_cmd - missing struct keyword
typedef struct s_cmd
{
	char						**argv;
	t_redirs				*redirs;
	pid_t						pid;        // use pid_t instead of t_pid
	int							is_builin;
	struct s_cmd		*next;      // need 'struct' keyword
}   t_cmd;

// Add missing fields to t_pipeline
typedef struct s_pipeline
{
    t_cmd		*commands;
    int			*pipes_fds;
    pid_t		*pids;              // use pid_t
    int			cmd_count;          // NEW: how many commands?
    int			pipe_count;         // NEW: how many pipes? (cmd_count - 1)
}   t_pipeline;

// Expand exec_context with essentials
typedef struct s_exec_context
{
    char    **envp;
    char    *paths;
    int     exit_status;
    int     stdin_backup;       // NEW: to restore stdin after redirections
    int     stdout_backup;      // NEW: to restore stdout after redirections
}   t_exec_context;

int	lexer(char *input, t_list **token_list);

#endif
