#include "../../../includes/minishell.h"

static int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while ((s1[i] || s2[i]) && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

static int	is_delimiter_line(char *line, char *delimiter)
{
	if (line == NULL || delimiter == NULL)
		return (1);
	return (ft_strcmp(line, delimiter) == 0);
}

static int	write_line_to_file(char *line, int fd)
{
	if (write(fd, line, ft_strlen(line)) == -1)
		return (EXIT_FAILURE);
	if (write(fd, "\n", 1) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	read_heredoc_input(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			break ;
		if (is_delimiter_line(line, delimiter))
		{
			free(line);
			break ;
		}
		if (write_line_to_file(line, fd) == EXIT_FAILURE)
		{
			free(line);
			return (EXIT_FAILURE);
		}
		free(line);
	}
	return (EXIT_SUCCESS);
}
