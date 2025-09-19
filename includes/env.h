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
char	*get_env_value(char **env, char *key, int last_exit_status);
char	**copy_env(char **envp, unsigned int expand);

#endif
