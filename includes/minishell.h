#ifndef MINISHELL_H
# define MINISHELL_H

#include "includes.h"

// ------------ EXECUTION PART ------------ //
void	exec_command_list(t_exec_context *exec_context);

// execution/execute.c
void	exec_builtin(t_exec_context *exec_context, t_cmd *builtin);
int	launch_child_process(t_exec_context *exec_context, t_cmd *command);

// find_executable.c
char	*look_up_cmdpath(char *cmd, char *paths, int *err_status);

// execution/redirect.c
void	setup_redirections(t_redirs *redirs);
void	set_in_fd(
	t_exec_context *exec_context, t_cmd *command, t_redirs *redirs);
void	set_out_fd(
	t_exec_context *exec_context, t_cmd *command, t_redirs *redirs);

// utils/init_shell.c
void	init_context(t_exec_context *exec_context, char **envp);

// utils/signals.c
void	setup_signals(int is_heredoc);
int	handle_pending_signals(t_exec_context *exec_context);

// utils/clean_up.c
void	free_str_arr(char **arr);
void	clean_up_commands(t_exec_context *exec_context);

// utils/env_utils.c
void		print_env(t_exec_context *exec_context, int out_fd);
size_t	env_len(char **arr);
char		**look_up_envname(t_exec_context *exec_context, char *name);
int			modify_envp(t_exec_context *ctx, int s, char *name);

// utils/error_utils.c
void	fatal_error(t_exec_context *exec_context, char *msg);
void	error_and_exit(char *err_msg, int exit_status);
// ---------------------------------------- //

// --------------- BUILTINS  -------------- //
int	ft_echo(t_cmd *cmd, int out_fd);
int	ft_cd(t_cmd *cmd, int out_fd);
int	ft_pwd(t_cmd *cmd, int out_fd);
int	ft_export(t_exec_context *exec_context, t_cmd *cmd, int out_fd);
int	ft_unset(t_exec_context *exec_context, t_cmd *cmd);
int	ft_env(t_exec_context *exec_context, t_cmd *cmd, int out_fd);
int	ft_exit(t_cmd *cmd, int out_fd);

int	check_arg(char *arg);
// ---------------------------------------- //

void debug_lexer(t_list *token_list, const char *input);
void debug_parser(t_cmd *cmd_head, const char *input);
void debug_lexer_and_parser(t_list *token_list, t_cmd *cmd_head, const char *input);
void debug_input(const char *test_input);

#endif
