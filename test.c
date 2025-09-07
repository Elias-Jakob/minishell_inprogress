#include "includes/env.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	int		i;
	char	**env;

	env = copy_env(envp, 0);
	env = set_env_variable(env, "LEO", "Leonardo");
	printf("%s\n", get_env_value(env, "LEO"));
	sleep(2);
	env = set_env_variable(env, "LEO", "Hello new var");
	printf("%s\n", get_env_value(env, "LEO"));
	sleep(2);
	char *str = "LEO";
	str = expand_variables(str, env);
	printf("%s\n", str);
	env = unset_env_variable(env, "LEO");
	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
	sleep(1);
	free_env(env);
	return (0);
}
