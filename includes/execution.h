#ifndef EXECUTION_H
# define EXECUTION_H

// ------------ EXECUTION PART ------------ //
void	exec_command_list(t_exec_context *exec_context);

// execution/execute.c
void	exec_builtin(t_exec_context *exec_context, t_cmd *builtin);
int		launch_child_process(t_exec_context *exec_context, t_cmd *command);

// find_executable.c
char	*look_up_cmdpath(char *cmd, char *paths, int *err_status);

// execution/redirect.c
void	setup_redirections(t_redirs *redirs);
void	set_in_fd(
	t_exec_context *exec_context, t_cmd *command, t_redirs *redirs);
void	set_out_fd(
	t_exec_context *exec_context, t_cmd *command, t_redirs *redirs);

// --------------- BUILTINS  -------------- //
int		ft_echo(t_cmd *cmd, int out_fd);
int		ft_cd(t_cmd *cmd, int out_fd);
int		ft_pwd(t_cmd *cmd, int out_fd);
int		ft_export(t_exec_context *exec_context, t_cmd *cmd, int out_fd);
int		ft_unset(t_exec_context *exec_context, t_cmd *cmd);
int		ft_env(t_exec_context *exec_context, t_cmd *cmd, int out_fd);
int		ft_exit(t_cmd *cmd, int out_fd);

int		check_arg(char *arg);
// ---------------------------------------- //

#endif
