#include "../../../includes/parser.h"

int	handle_input_redirection(t_cmd *cmd, t_token *file_token)
{
	cmd->redirs->in_type = RD_FILE;
	cmd->redirs->infile_name = ft_strdup(file_token->value);
	if (cmd->redirs->infile_name == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	handle_output_redirection(t_cmd *cmd, t_token *file_token)
{
	cmd->redirs->out_type = RD_FILE;
	cmd->redirs->outfile_name = ft_strdup(file_token->value);
	if (cmd->redirs->outfile_name == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	handle_append_redirection(t_cmd *cmd, t_token *file_token)
{
	cmd->redirs->out_type = RD_APPEND_OUT;
	cmd->redirs->outfile_name = ft_strdup(file_token->value);
	if (cmd->redirs->outfile_name == NULL)
		return (EXIT_FAILURE);
	cmd->redirs->append_mode = 1;
	return (EXIT_SUCCESS);
}

int	handle_heredoc_redirection(t_cmd *cmd, t_token *delimiter_token)
{
	char	*tmp_file_path;

	cmd->redirs->heredoc_delimiter = ft_strdup(delimiter_token->value);
	if (cmd->redirs->heredoc_delimiter == NULL)
		return (EXIT_FAILURE);
	if (create_heredoc_file(delimiter_token->value, &tmp_file_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	cmd->redirs->in_type = RD_HEREDOC;
	cmd->redirs->infile_name = tmp_file_path;
	return (EXIT_SUCCESS);
}
