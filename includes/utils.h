#ifndef UTILS_H
# define UTILS_H

// utils/init_shell.c
void	init_context(t_exec_context *exec_context, char **envp);

// utils/signals.c
void	default_sigint_handler(int signal);
void	exec_sigint_handler(int signal);
void	heredoc_sigint_handler(int signal);
int		handle_pending_signals(t_exec_context *exec_context);
void	change_signal_settings(void (*hander_func)(int),
		t_exec_context *exec_context);
void	setup_signals(void);

// utils/clean_up.c
void	free_str_arr(char **arr);
void	clean_up_commands(t_exec_context *exec_context);

// utils/error_utils.c
void	fatal_error(t_exec_context *exec_context, char *msg);
void	error_and_exit(char *err_msg, int exit_status);

#endif
