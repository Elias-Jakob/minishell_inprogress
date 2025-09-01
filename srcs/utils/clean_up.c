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
	if (redirs->fds[0] != STDIN_FILENO)
		close(redirs->fds[0]);
	if (redirs->fds[1] != STDOUT_FILENO)
		close(redirs->fds[1]);
	free(redirs);
}

void	clean_up_commands(t_exec_context *exec_context)
{
	t_cmd	*current_cmd;
	t_cmd	*last_cmd;

	current_cmd = exec_context->commands;
	while (current_cmd)
	{
		free_str_arr(current_cmd->argv);
		if (current_cmd->redirs)
			clean_up_redirs(current_cmd->redirs);
		last_cmd = current_cmd;
		current_cmd = current_cmd->next;
		free(last_cmd);
	}
}
