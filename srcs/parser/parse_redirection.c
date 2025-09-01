#include "../../includes/minishell.h"

static void	set_redir(char **file_name, char *value, t_redirs_type *in_out_type,
			t_redirs_type type)
{
	*file_name = ft_strdup(value);
	*in_out_type = type;
}

static t_list	*set_cmd_redirection(t_list *current, t_token *token,
				t_cmd *cmd)
{
	t_token	*file_token;

    file_token = (t_token *)current->content;
    if (token->type == TK_REDIRECT_IN)
		set_redir(&cmd->redirs->infile_name, file_token->value,
				&cmd->redirs->in_type, RD_STD);
    else if (token->type == TK_REDIRECT_OUT)
		set_redir(&cmd->redirs->infile_name, file_token->value,
				&cmd->redirs->out_type, RD_FD);
    else if (token->type == TK_APPEND_OUT)
		set_redir(&cmd->redirs->infile_name, file_token->value,
				&cmd->redirs->out_type, RD_APPEND_OUT);
    else if (token->type == TK_HEREDOC)
		set_redir(&cmd->redirs->infile_name, file_token->value,
				&cmd->redirs->out_type, RD_HEREDOC);
    return (current->next);
}

t_list	*parse_redirection(t_cmd *cmd, t_list *current)
{
    t_token	*token;

	token = (t_token *)current->content;
    if (!cmd || !current)
        return current;
    if (!cmd->redirs)
    {
        cmd->redirs = malloc(sizeof(t_redirs));
        ft_memset(cmd->redirs, 0, sizeof(t_redirs));
    }
    if (token->type == TK_PIPE)
    {
        cmd->redirs->out_type = RD_PIPE;
        return (current->next);
    }
    current = current->next;
	if (!current || !current->content)
		return (current);
	return (set_cmd_redirection(current, token, cmd));
}
