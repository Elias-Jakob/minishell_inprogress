#include "../../includes/minishell.h"

int	is_token_redirect(t_token_type type)
{
    return (type == TK_REDIRECT_IN || type == TK_REDIRECT_OUT
            || type == TK_HEREDOC || type == TK_APPEND_OUT
			|| type == TK_PIPE);
}

int	is_token_word(t_token_type type)
{
    return (type == TK_WORD || type == TK_DOUBLE_QUOTE);
}

void	append_cmd(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*last;

    if (!*head)
        *head = new_cmd;
    else
    {
        last = *head;
        while (last->next)
            last = last->next;
        last->next = new_cmd;
    }
}

void init_redirs_if_needed(t_cmd *cmd)
{
    if (!cmd->redirs)
    {
        cmd->redirs = malloc(sizeof(t_redirs));
        ft_memset(cmd->redirs, 0, sizeof(t_redirs));
    }
}

int	get_argv_amount(t_list *start)
{
    t_list  *current;
    t_token *token;
    int     count;

	count = 0;
	current = start;
    while (current)
    {
        token = (t_token *)current->content;
        if (!token)
            break;
        if (is_token_word(token->type))
            count++;
        else if (is_token_redirect(token->type))
            current = current->next;
        current = current->next;
    }
    return (count);
}
