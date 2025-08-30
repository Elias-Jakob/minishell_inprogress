#include "../../includes/minishell.h"

// heredoc ?

void	set_in_fd(t_cmd *command, t_redirs *redirs)
{
	if ((redirs->type == RD_FILE
		|| redirs->type == RD_APPEND) && redirs->infile_name)
	{
		redirs->fds[0] = open(redirs->infile_name, O_RDONLY);
		// TODO: check if files exists & and we have the right permissions
		if (redirs->fds[0] == -1)
			error_and_exit(command->argv[0], 1);
	}
	else if (redirs->type == RD_FD && redirs->infile_name)
		redirs->fds[0] = ft_atoi(redirs->infile_name);
	// TODO: Implement heredoc
	else if (redirs->type == RD_HEREDOC)
		;
}

void	set_out_fd(t_cmd *command, t_redirs *redirs)
{
	int	oflag;
	int	pipe_fds[2];

	if (redirs->outfile_name)
	{
		oflag = O_WRONLY | O_CREAT | O_TRUNC;
		if (redirs->type == RD_APPEND)
			oflag = O_WRONLY | O_CREAT | O_APPEND;
		redirs->fds[1] = open(redirs->outfile_name, oflag, 0644);
		if (redirs->fds[1] == -1)
			error_and_exit(command->argv[0], 1);
	}
	else if (redirs->type == RD_FD && redirs->outfile_name)
		redirs->fds[1] = ft_atoi(redirs->outfile_name);
	else if (redirs->type == RD_PIPE)
	{
		if (pipe(pipe_fds) == -1)
			error_and_exit("pipe failed", 1);
		redirs->fds[1] = pipe_fds[1];
		if (command->next)
			command->next->redirs->fds[0] = pipe_fds[0];
	}
	else if (redirs->type == RD_HEREDOC)
		;
}

void	setup_redirections(t_redirs *redirs)
{
	if (redirs->fds[0] != STDIN_FILENO)
	{
		if (dup2(redirs->fds[0], STDIN_FILENO) == -1)
			error_and_exit("dup2 failed", 1);
		if (close(redirs->fds[0]) == -1)
			error_and_exit("close failed", 1);
	}
	if (redirs->fds[1] != STDOUT_FILENO)
	{
		if (dup2(redirs->fds[1], STDOUT_FILENO) == -1)
			error_and_exit("dup2 failed", 1);
		if (close(redirs->fds[1]) == -1)
			error_and_exit("close failed", 1);
	}
}
