#include "../../../includes/parser.h"

t_token *get_current_token(t_list *token_list)
{
    if (token_list)
        return ((t_token *)(token_list->content));
    return (NULL);
}

t_token *get_next_token(t_list *token_list)
{
    if (token_list && token_list->next)
        return ((t_token *)(token_list->next->content));
    return (NULL);
}

t_list *advance_token_node(t_list *current_node)
{
    if (current_node)
        return (current_node->next);
    return (NULL);
}

int is_redirection_token(t_token *token)
{
    if (token == NULL)
        return (0);
    return (token->type == TK_REDIRECT_IN || token->type == TK_REDIRECT_OUT ||
            token->type == TK_APPEND_OUT || token->type == TK_HEREDOC);
}

int is_token_builtin(t_token *token)
{
    if (token == NULL || token->value == NULL)
        return (EXIT_FAILURE);
    if (ft_strncmp(token->value, "echo", 5) == 0 &&
        ft_strlen(token->value) == 4)
        return (EXIT_SUCCESS);
    if (ft_strncmp(token->value, "cd", 3) == 0 && ft_strlen(token->value) == 2)
        return (EXIT_SUCCESS);
    if (ft_strncmp(token->value, "pwd", 4) == 0 && ft_strlen(token->value) == 3)
        return (EXIT_SUCCESS);
    if (ft_strncmp(token->value, "export", 7) == 0 &&
        ft_strlen(token->value) == 6)
        return (EXIT_SUCCESS);
    if (ft_strncmp(token->value, "unset", 6) == 0 &&
        ft_strlen(token->value) == 5)
        return (EXIT_SUCCESS);
    if (ft_strncmp(token->value, "env", 4) == 0 && ft_strlen(token->value) == 3)
        return (EXIT_SUCCESS);
    if (ft_strncmp(token->value, "exit", 5) == 0 &&
        ft_strlen(token->value) == 4)
        return (EXIT_SUCCESS);
    return (EXIT_FAILURE);
}
