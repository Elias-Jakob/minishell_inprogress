#include "../../includes/minishell.h"

#ifndef RED
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOWN  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#endif

static char *token_type_to_str(t_token_type type)
{
    switch (type)
    {
        case TK_WORD:           return ("WORD");
        case TK_PIPE:           return ("PIPE");
        case TK_REDIRECT_IN:    return ("REDIRECT_IN");
        case TK_REDIRECT_OUT:   return ("REDIRECT_OUT");
        case TK_APPEND_OUT:     return ("APPEND_OUT");
        case TK_HEREDOC:        return ("HEREDOC");
        case TK_ENV:            return ("ENV_VAR");
        case TK_SINGLE_QUOTE:   return ("SINGLE_QUOTE");
        case TK_DOUBLE_QUOTE:   return ("DOUBLE_QUOTE");
        case TK_ERROR:          return ("ERROR");
        default:                return ("UNKNOWN");
    }
}

static void print_token_details(t_token *token, int index)
{
    if (!token)
    {
        printf("  [%d] Token: NULL\n", index);
        return;
    }
    printf("  [%d] Type: %-15s | Value: \"%s\"\n", 
           index, 
           token_type_to_str(token->type),
           token->value ? token->value : "(null)");
}

void debug_lexer(t_list *token_list, const char *input)
{
    printf("\n" CYAN "========================================\n");
    printf("           LEXER DEBUG OUTPUT\n");
    printf("========================================" RESET "\n");
    if (!input)
        printf("Input: " RED "(NULL)" RESET "\n");
    else
        printf("Input: \"" YELLOWN "%s" RESET "\"\n", input);
    if (!token_list)
    {
        printf(RED "🛂 Token list is NULL!\n" RESET);
        printf("========================================\n\n");
        return;
    }
    int token_count = 0;
    t_list *current = token_list;
    while (current)
    {
        token_count++;
        current = current->next;
    }
    printf("Token count: " GREEN "%d" RESET "\n", token_count);
    printf("----------------------------------------\n");
    current = token_list;
    int index = 0;
    while (current)
    {
        print_token_details((t_token *)current->content, index);
        current = current->next;
        index++;
    }
    printf("========================================\n\n");
}

static char *redir_type_to_str(t_redirs_type type)
{
    switch (type)
    {
        case RD_STD:        return ("STANDARD");
        case RD_FILE:       return ("FILE");
        case RD_APPEND_OUT: return ("APPEND");
        case RD_FD:         return ("FILE_DESCRIPTOR");
        case RD_PIPE:       return ("PIPE");
        case RD_HEREDOC:    return ("HEREDOC");
        default:            return ("UNKNOWN");
    }
}

static void print_redirection_details(t_redirs *redirs)
{
    if (!redirs)
    {
        printf("    Redirections: " RED "None" RESET "\n");
        return;
    }
    printf("    Redirections:\n");
    if (redirs->in_type != RD_STD)
    {
        printf("      Input:  %s", redir_type_to_str(redirs->in_type));
        if (redirs->infile_name)
            printf(" -> \"%s\"", redirs->infile_name);
        if (redirs->heredoc_delimiter)
            printf(" (delimiter: \"%s\")", redirs->heredoc_delimiter);
        printf("\n");
    }
    if (redirs->out_type != RD_STD)
    {
        printf("      Output: %s", redir_type_to_str(redirs->out_type));
        if (redirs->outfile_name)
            printf(" -> \"%s\"", redirs->outfile_name);
        if (redirs->append_mode)
            printf(" (append mode)");
        printf("\n");
    }
	printf("      FDs: [%d, %d]\n", redirs->fds[0], redirs->fds[1]);
}

static void print_command_details(t_cmd *cmd, int cmd_index)
{
    if (!cmd)
    {
        printf("  " RED "Command %d: NULL" RESET "\n", cmd_index);
        return;
    }
    printf("  " GREEN "Command %d:" RESET "\n", cmd_index);
    printf("    Address: %p\n", (void*)cmd);
    if (!cmd->argv)
    {
        printf("    Arguments: " RED "NULL" RESET "\n");
    }
    else if (!cmd->argv[0])
    {
        printf("    Arguments: " RED "Empty array" RESET "\n");
    }
    else
    {
        printf("    Arguments:\n");
        for (int i = 0; cmd->argv[i]; i++)
        {
            if (i == 0)
                printf("      [%d] " BLUE "%s" RESET " (command)\n", 
                       i, cmd->argv[i]);
            else
                printf("      [%d] %s\n", i, cmd->argv[i]);
        }
    }
    print_redirection_details(cmd->redirs);
    printf("    Builtin: %s\n", cmd->is_builtin ? "Yes" : "No");
    printf("    PID: %d\n", cmd->pid);
    printf("    Exit status: %d\n", cmd->exit_status);
    printf("    Next command: %p\n", (void*)cmd->next);
    printf("\n");
}

void debug_parser(t_cmd *cmd_head, const char *input)
{
    printf("\n" MAGENTA "========================================\n");
    printf("           PARSER DEBUG OUTPUT\n");
    printf("========================================" RESET "\n");
    if (!input)
        printf("Input: " RED "(NULL)" RESET "\n");
    else
        printf("Input: \"" YELLOWN "%s" RESET "\"\n", input);
    if (!cmd_head)
    {
        printf(RED "🛂 Command list is NULL!\n" RESET);
        printf("========================================\n\n");
        return;
    }
    int cmd_count = 0;
    t_cmd *current = cmd_head;
    while (current)
    {
        cmd_count++;
        current = current->next;
    }
    
    printf("Command count: " GREEN "%d" RESET "\n", cmd_count);
    printf("Pipeline detected: %s\n", (cmd_count > 1) ? "Yes" : "No");
    printf("----------------------------------------\n");
    current = cmd_head;
    int cmd_index = 0;
    while (current)
    {
        print_command_details(current, cmd_index);
        current = current->next;
        cmd_index++;
    }
    printf("========================================\n\n");
}

void debug_lexer_and_parser(t_list *token_list, t_cmd *cmd_head, const char *input)
{
	debug_lexer(token_list, input);
	debug_parser(cmd_head, input);
}

static void free_token(void *content)
{
	t_token *token = (t_token *)content;
	if (!token)
		return;
	if (token->value)
		free(token->value);
	free(token);
}

void debug_input(const char *test_input)
{
	t_list *token_list = NULL;
	t_cmd *cmd_head = NULL;

	printf("\n" CYAN "=== TESTING INPUT: \"%s\" ===" RESET "\n", test_input);
	if (lexer((char*)test_input, &token_list) != 0)
	{
		printf(RED "🛂 Lexer failed!\n" RESET);
		return;
	}
	if (parser(token_list, &cmd_head) != 0)
	{
		printf(RED "🛂 Parser failed!\n" RESET);
	}
	debug_lexer_and_parser(token_list, cmd_head, test_input);
	ft_lstclear(&token_list, free_token);
}
