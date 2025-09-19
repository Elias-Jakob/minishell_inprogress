#ifndef ENV_H
# define ENV_H

#include <stdio.h>
#include "libft.h"

void	free_env(char **env);
char	**reset_env_variable(char **env, char *key, char *value);
char	**set_new_env_variable(char **env, char *key, char *value);
char	*expand_variables(char *str, char **env);

char	**unset_env_variable(char **env, char *key);
char	**set_env_variable(char **env, char *key, char *value);
char	**copy_env(char **envp, unsigned int expand);
// char		*expand_variables(char *str, char **env);
char		*get_env_value(char **env, char *key);

char		**copy_envp(char **envp);
void		print_env(t_exec_context *exec_context, int out_fd);
size_t	env_len(char **arr);
char		**look_up_envname(t_exec_context *exec_context, char *name);
int			modify_envp(t_exec_context *ctx, int s, char *name);
#endif
