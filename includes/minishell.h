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

typedef enum e_redir_type
{
	RD_STD,
	RD_FILE,
	RD_APPEND_OUT,
	RD_FD,
	RD_PIPE,
	RD_HEREDOC
}	t_redirs_type;

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

// ---------------- LEXER ---------------- //
// utils
int is_space(char c);
char *ft_strndup(const char *s1, size_t n);

// scan_token
t_token_type	scan_for_quotes(char *input, size_t *length);
t_token_type	scan_for_word(char *input, size_t *length);
t_token_type	scan_for_env(char *input, size_t *length);
t_token_type	scan_for_redirect(char *input, size_t *length);
t_token_type	scan_for_token_type(char *input, size_t *length);

// lexer
int	lexer(char *input, t_list **token_list);
// ---------------------------------------- //


// ---------------- PARSER ---------------- //
// utils
int	is_token_redirect(t_token_type type);
int	is_token_word(t_token_type type);
void	append_cmd(t_cmd **head, t_cmd *new_cmd);
void	init_redirs_if_needed(t_cmd *cmd);
int	get_argv_amount(t_list *start);

// parse redirections
t_list	*parse_redirection(t_cmd *cmd, t_list *current);


int parser(t_list *token_list, t_cmd **cmd_head);
// ---------------------------------------- //

// EXECUTION PART

// execution/pipeline.c
// void	run_pipeline(t_pipeline *pipeline, t_exec_context *exec_context);
//
// // execution/execute.c
// int	exec_builtin(t_exec_context *exec_context, t_cmd *builtin);
// int	exec_command(t_exec_context *exec_context, t_cmd *command);
//
// // execution/redirect.c
// void	setup_redirections(t_redirs *redirs);
// void	set_in_fd(t_cmd *command, t_redirs *redirs);
// void	set_out_fd(t_cmd *command, t_redirs *redirs);
//
// // utils/clean_up.c
// void	error_and_exit(char *err_msg, int exit_status);

#endif
