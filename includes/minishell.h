#ifndef MINISHELL_H
# define MINISHELL_H

#include "includes.h"
#include "env.h"
#include "parser.h"
#include "lexer.h"

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

typedef enum e_redir_type
{
	RD_STD,
	RD_FILE,
	RD_APPEND_OUT,
	RD_FD,
	RD_PIPE,
	RD_HEREDOC
}	t_redirs_type;

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


// ------------ EXECUTION PART ------------ //
void	exec_command_list(t_exec_context *exec_context);

// execution/execute.c
int	exec_builtin(t_exec_context *exec_context, t_cmd *builtin);
int	launch_child_process(t_exec_context *exec_context, t_cmd *command);

// find_executable.c
char	*look_up_cmdpath(char *cmd, char *paths, int *err_status);

// execution/redirect.c
void	setup_redirections(t_redirs *redirs);
void	set_in_fd(
	t_exec_context *exec_context, t_cmd *command, t_redirs *redirs);
void	set_out_fd(
	t_exec_context *exec_context, t_cmd *command, t_redirs *redirs);

// execution/init_context.c
void	init_exec(t_exec_context *exec_context, char **envp);

// utils/clean_up.c
void	free_str_arr(char **arr);
void	clean_up_commands(t_exec_context *exec_context);

// utils/error_utils.c
void	fatal_error(t_exec_context *exec_context, char *msg);
void	error_and_exit(char *err_msg, int exit_status);
// ---------------------------------------- //

// --------------- BUILTINS  -------------- //
int	ft_echo(t_cmd *cmd, int out_fd);
int	ft_cd(t_cmd *cmd, int out_fd);
int	ft_pwd(t_cmd *cmd, int out_fd);
int	ft_exit(t_cmd *cmd, int out_fd);
// ---------------------------------------- //

void debug_lexer(t_list *token_list, const char *input);
void debug_parser(t_cmd *cmd_head, const char *input);
void debug_lexer_and_parser(t_list *token_list, t_cmd *cmd_head, const char *input);
void debug_input(const char *test_input);

#endif
