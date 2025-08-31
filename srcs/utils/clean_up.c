#include "../../includes/minishell.h"

void	free_str_arr(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static void	clean_up_redirs(t_redirs *redirs)
{
	free(redirs->infile_name);
	free(redirs->outfile_name);
	free(redirs->heredoc_delimiter);
	free(redirs->heredoc_content);
	if (redirs->fds[0] != STDIN_FILENO && close(redirs->fds[0]))
		perror("close failed");
	if (redirs->fds[1] != STDOUT_FILENO && close(redirs->fds[1]))
		perror("close failed");
}

void	clean_up_commands(t_exec_context *exec_context)
{
	t_cmd	*curent_cmd;
	t_cmd	*last_cmd;

	curent_cmd = exec_context->commands;
	while (curent_cmd)
	{
		free_str_arr(curent_cmd->argv);
		if (curent_cmd->redirs)
			clean_up_redirs(curent_cmd->redirs);
		last_cmd = curent_cmd;
		curent_cmd = curent_cmd->next;
		free(last_cmd);
	}
}
