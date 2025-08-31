#include "../../includes/minishell.h"

int	is_token_redirect(t_token_type type)
{
	return (type == TK_REDIRECT_IN || type == TK_REDIRECT_OUT
			|| type == TK_HEREDOC || type == TK_APPEND_OUT || type == TK_PIPE);
}

int	is_token_word(t_token_type type)
{
	return (type == TK_WORD || type == TK_DOUBLE_QUOTE);
}

static int get_argv_amount(t_list *start)
{
    t_list  *current = start;
    t_token *token;
    int     count = 0;

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
//
// int parser(t_list *token_list, t_list **cmd_list)
// {
//     t_list  *current = token_list;
//     t_token *token;
//     t_cmd   cmd;
//     int     arg_amount;
//
//     while (current)
//     {
//         arg_amount = get_argv_amount(current);
//         if (arg_amount <= 0)
//         {
//             current = current->next;
//             continue;
//         }
//         cmd.argv = malloc(sizeof(char *) * (arg_amount + 1));
//         if (!cmd.argv)
//             return (EXIT_FAILURE);
//         int i = 0;
//         while (i < arg_amount && current)
//         {
//             token = (t_token *)current->content;
//             if (!token || !token->value)
//                 break;
//
//             cmd.argv[i] = ft_strdup(token->value);
//             current = current->next;
//             i++;
//         }
//         cmd.argv[i] = NULL;
//         t_cmd *new_cmd = malloc(sizeof(t_cmd));
//                if (!new_cmd)
//                        return (EXIT_FAILURE);
//         new_cmd->argv = cmd.argv;
//         t_list *new = ft_lstnew(new_cmd);
//                if (!new)
//                        return (EXIT_FAILURE);
//         ft_lstadd_back(cmd_list, new);
//     }
//     return (EXIT_SUCCESS);
// }

void	add_argv_from_token(t_cmd *cmd, t_token *token, int index)
{
	if (!cmd || !token || !token->value)
		return ;
	cmd->argv[index] = ft_strdup(token->value);
}

t_list *parse_redirection(t_cmd *cmd, t_list *current)
{
    t_token *token = (t_token *)current->content;

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
        return current->next; // pipe termine cette commande
    }
    current = current->next;
    if (!current || !current->content)
        return current;
    t_token *file_token = (t_token *)current->content;
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

int parse_command(t_list **current_tk_list, t_list **cmd_list)
{
    t_list  *current = *current_tk_list;
    t_token *token;
    t_cmd   cmd;
    int     argv_count, i;

    ft_memset(&cmd, 0, sizeof(t_cmd));
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
                if (cmd.argv)
                    cmd.argv[i] = NULL;
                t_cmd *new_cmd = malloc(sizeof(t_cmd));
                *new_cmd = cmd;
                t_list *new_node = ft_lstnew(new_cmd);
                ft_lstadd_back(cmd_list, new_node);
                *current_tk_list = next;
                return EXIT_SUCCESS;
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
        t_list *new_node = ft_lstnew(new_cmd);
        ft_lstadd_back(cmd_list, new_node);
    }
    *current_tk_list = current;
    return EXIT_SUCCESS;
}

int parser(t_list *token_list, t_list **cmd_list)
{
    t_list *current = token_list;
    while (current)
        parse_command(&current, cmd_list);
    return EXIT_SUCCESS;
}
