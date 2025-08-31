#include "../../includes/minishell.h"

void add_argv_from_token(t_cmd *cmd, t_token *token, int index)
{
    if (!cmd || !token || !token->value)
        return ;
    cmd->argv[index] = ft_strdup(token->value);
}

t_list	*set_cmd_redirection(t_list *current, t_token *token)
{
	t_token	*file_token;

    file_token = (t_token *)current->content;
    if (token->type == TK_REDIRECT_IN)
    {
        cmd->redirs->infile_name = ft_strdup(file_token->value);
        cmd->redirs->out_type = RD_STD;
    }
    else if (token->type == TK_REDIRECT_OUT)
    {
        cmd->redirs->outfile_name = ft_strdup(file_token->value);
        cmd->redirs->out_type = RD_FD;
    }
    else if (token->type == TK_APPEND_OUT)
    {
        cmd->redirs->outfile_name = ft_strdup(file_token->value);
        cmd->redirs->out_type = RD_APPEND_OUT;
    }
    else if (token->type == TK_HEREDOC)
    {
        cmd->redirs->heredoc_delimiter = ft_strdup(file_token->value);
        cmd->redirs->out_type = RD_HEREDOC;
    }
    return current->next;
}

t_list *parse_redirection(t_cmd *cmd, t_list *current)
{
    t_token *token;

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
        return current;
}

int parse_command(t_list **current_tk_list, t_cmd **cmd_head, int pipe_in)
{
    t_list  *current = *current_tk_list;
    t_token *token;
    t_cmd   cmd;
    int     argv_count, i;

    ft_memset(&cmd, 0, sizeof(t_cmd));
    if (pipe_in)
    {
        init_redirs_if_needed(&cmd);
        cmd.redirs->in_type = RD_PIPE;
    }

    argv_count = get_argv_amount(current);
    if (argv_count > 0)
    {
        cmd.argv = malloc(sizeof(char *) * (argv_count + 1));
        if (!cmd.argv)
            return (EXIT_FAILURE);
    }
    i = 0;
    while (current)
    {
        token = (t_token *)current->content;
        if (!token)
            break;
        if (is_token_word(token->type))
        {
            cmd.argv[i++] = ft_strdup(token->value);
            current = current->next;
        }
        else if (is_token_redirect(token->type))
        {
            t_list *next = parse_redirection(&cmd, current);
            if (token->type == TK_PIPE)
            {
                init_redirs_if_needed(&cmd);
                cmd.redirs->out_type = RD_PIPE;
                if (cmd.argv)
                    cmd.argv[i] = NULL;

                t_cmd *new_cmd = malloc(sizeof(t_cmd));
                *new_cmd = cmd;
                new_cmd->next = NULL;
                append_cmd(cmd_head, new_cmd);

                *current_tk_list = next;
                // relancer en précisant que la prochaine commande a un in_type = PIPE
                return parse_command(current_tk_list, cmd_head, 1);
            }
            current = next;
        }
        else
            current = current->next;
    }
    if (cmd.argv)
        cmd.argv[i] = NULL;
    if (cmd.argv || cmd.redirs)
    {
        t_cmd *new_cmd = malloc(sizeof(t_cmd));
        *new_cmd = cmd;
        new_cmd->next = NULL;
        append_cmd(cmd_head, new_cmd);
    }
    *current_tk_list = current;
    return (EXIT_SUCCESS);
}

int parser(t_list *token_list, t_cmd **cmd_head)
{
    t_list *current = token_list;
    while (current)
        parse_command(&current, cmd_head, 0);
    return EXIT_SUCCESS;
}
