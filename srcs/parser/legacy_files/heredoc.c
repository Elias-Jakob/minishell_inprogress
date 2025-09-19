#include "../../../includes/parser.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

void	cleanup_heredoc(t_redirs *redir)
{
	if (redir && redir->heredoc_content)
	{
		if (unlink(redir->heredoc_content) == -1)
			perror("minishell: unlink heredoc");
		free(redir->heredoc_content);
		redir->heredoc_content = NULL;
	}
}

static char	*generate_heredoc_filename(void)
{
	static int	heredoc_counter = 0;
	char		*filename;
	char		*counter_str;
	char		*tmp_path;

	counter_str = ft_itoa(heredoc_counter++);
	if (counter_str == NULL)
		return (NULL);
	tmp_path = ft_strjoin("__heredoc__", counter_str);
	free(counter_str);
	if (tmp_path == NULL)
		return (NULL);
	filename = ft_strjoin("/tmp/", tmp_path);
	free(tmp_path);
	return (filename);
}

int	create_heredoc_file(char *delimiter, char **tmp_file_path)
{
	int		fd;
	char	*line;
	char	*filename;

	filename = generate_heredoc_filename();
	if (filename == NULL)
		return (EXIT_FAILURE);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("minishell: heredoc");
		free(filename);
		return (EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	*tmp_file_path = filename;
	return (EXIT_SUCCESS);
}
