#include "../../includes/minishell.h"

int parse_command(t_list **current_tk_list, t_cmd **cmd_head, int pipe_in)
{
    t_list  *current;
    t_token *token;
    t_cmd   cmd;
    int     argv_count;
	int		i;

	current = *current_tk_list;
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
