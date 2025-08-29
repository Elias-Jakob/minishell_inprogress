#include "../../includes/minishell.h"

// heredoc ?

static void	redirect_in(t_data *data, int fds[2])
{
	int	input_fd;

	if (data->i == 2)
	{
		input_fd = open(data->argv[1], O_RDONLY);
		if (input_fd == -1)
		{
			perror(data->argv[1]);
			if (close(fds[0]) == -1
				|| close(fds[1]) == -1)
				perror("close failed");
			exit(1);
		}
	}
	else
		input_fd = fds[0];
	if (dup2(input_fd, 0) == -1)
		error_and_exit("dup2 failed", 1);
	if (close(input_fd) == -1)
		error_and_exit("close failed", 1);
}

static void	redirect_out(t_data *data, int fds[2])
{
	int	output_fd;
	int	oflag;

	if (data->i == data->argc - 2)
	{
		oflag = O_WRONLY | O_CREAT | O_TRUNC;
		output_fd = open(data->argv[data->argc - 1], oflag, 0644);
		if (output_fd == -1)
			error_and_exit(data->argv[data->argc - 1], 1);
	}
	else
		output_fd = fds[1];
	if (dup2(output_fd, 1) == -1)
		error_and_exit("dup2 failed", 1);
	if (close(output_fd) == -1)
		error_and_exit("close failed", 1);
}

void	redirect_in(t_cmd *command, t_redirs *redirs)
{
	if (redirs->in_file)
	{
		redirs->fds[0] = open(redirs->in_file, O_RDONLY);
		// TODO: check if files exists & and we have the right permissions
		if (redirs->fds[0] == -1)
		{
			perror(command->argv[0]);
			exit(1);
		}
	}
	if (dup2(redirs->fds[0], STDIN_FILENO) == -1)
	{
		perror("dup2 failed");
		eixt(1);
	}
	// checks if the in is a pipe and if so closes it
	// really??
	if (redirs->is_pipe && close(redirs->in_fd[0]) == -1)
	{
		perror("close failed");
		exit(1);
	}
}

void	redirect_out(t_cmd *command, t_redirs *redirs)
{
	int	oflag;
	// TODO: if pipe then set in_fd of the next command to read end of the pipe
	if (redirs->is_pipe && command->next)
	{
		if (pipe(fds) == -1)
		{
			perror("pipe failed");
			exit(1);
		}
	}
	if (redirs->out_file)
	{
		if (redirs->append_mode)
			oflag = O_WRONLY | O_CREAT | O_APPEND;
		else
			oflag = O_WRONLY | O_CREAT | O_TRUNC;
		redirs->fds[1] = open(redirs->in_file, oflag);
		if (redirs->fds[1] == -1)
		{
			perror(command->argv[0]);
			exit(1);
		}
	}
	if (dup2(redirs->fds[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		exit(1);
	}
	if (close(fds[1]) == -1)
	{
		perror("close failed");
		exit(1);
	}
}


