#include "../../../includes/minishell.h"

int	ensure_redirection_exists(t_cmd *cmd)
{
	if (cmd->redirs == NULL)
	{
		cmd->redirs = init_redirection();
		if (cmd->redirs == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_redirs	*init_redirection(void)
{
	t_redirs	*new_redir;

	new_redir = malloc(sizeof(t_redirs));
	if (new_redir == NULL)
		return (NULL);
	new_redir->in_type = RD_STD;
	new_redir->out_type = RD_STD;
	new_redir->infile_name = NULL;
	new_redir->outfile_name = NULL;
	new_redir->heredoc_content = NULL;
	new_redir->heredoc_delimiter = NULL;
	new_redir->fds[0] = 0;
	new_redir->fds[1] = 1;
	new_redir->append_mode = 0;
	return (new_redir);
}
