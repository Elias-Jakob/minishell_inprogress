#include "../../../includes/minishell.h"

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
	static int	heredoc_counter;
	char		*filename;
	char		*counter_str;
	char		*tmp_path;

	heredoc_counter = 0;
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

char	*create_heredoc_temp_file(void)
{
	return (generate_heredoc_filename());
}
