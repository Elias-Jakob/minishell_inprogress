#include "../../../includes/minishell.h"

int	create_heredoc_file(char *delimiter, char **tmp_file_path)
{
	int		fd;
	char	*filename;

	filename = create_heredoc_temp_file();
	if (filename == NULL)
		return (EXIT_FAILURE);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("minishell: heredoc");
		free(filename);
		return (EXIT_FAILURE);
	}
	if (read_heredoc_input(fd, delimiter) == EXIT_FAILURE)
	{
		close(fd);
		unlink(filename);
		free(filename);
		return (EXIT_FAILURE);
	}
	close(fd);
	*tmp_file_path = filename;
	return (EXIT_SUCCESS);
}
