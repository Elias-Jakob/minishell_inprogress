#include "../../includes/minishell.h"

// Put into utils file
static int is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

// Put into utils
char *ft_strndup(const char *s1, size_t n)
{
	char *s2;
	size_t i;

	i = 0;
	// Use n instead of strlen
	s2 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!s2)
		return (NULL);
	while (s1[i] && i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

static t_token_type	scan_for_quotes(char *input, size_t *length)
{
	if (*input == '"')
	{
		while (input[*length])
		{
			(*length)++;
			if (input[*length] == '"')
			{
				(*length)++;
				return (TK_DOUBLE_QUOTE);
			}
		}
	}
	else if (*input == '\'')
	{
		while (input[*length])
		{
			(*length)++;
			if (input[*length] == '\'')
			{
				(*length)++;
				return (TK_SINGLE_QUOTE);
			}
		}
	}
	return (TK_ERROR);
}

static t_token_type	scan_for_word(char *input, size_t *length)
{
	while (input[*length])
	{
		(*length)++;
		if ((!ft_isalnum(input[*length]) && *input != '-') || is_space(input[*length]))
				return (TK_WORD);
	}
	return (TK_ERROR);
}

static t_token_type	scan_for_env(char *input, size_t *length)
{
	(*length)++;
	while (ft_isalpha(input[*length]))
		(*length)++;
	return (TK_ENV);
}

static t_token_type	scan_for_redirect(char *input, size_t *length)
{
	if (*input == '<')
	{
		(*length)++;
		if (*(input + 1) == '<')
		{
			(*length)++;
			return (TK_HEREDOC);
		}
		return (TK_REDIRECT_IN);
	}
	if (*input == '>')
	{
		(*length)++;
		if (*(input + 1) == '>')
		{
			(*length)++;
			return (TK_APPEND_OUT);
		}
		return (TK_REDIRECT_OUT);
	}
	return (TK_ERROR);
}

static t_token_type scan_for_token_type(char *input, size_t *length)
{
	if (*input == '|')
	{
		(*length)++;
		return (TK_PIPE);
	}
	if (*input == '<' || *input == '>')
		return (scan_for_redirect(input, length));
	if (*input == '$')
		return (scan_for_env(input, length));
	if (*input == '"' || *input == '\'')
		return (scan_for_quotes(input, length));
	if (ft_isalnum(*input) || *input == '-')
		return (scan_for_word(input, length));
	return (TK_ERROR);
}

static t_token *create_token(t_token_type type, char *input, size_t length)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strndup(input, length);
	return (token);
}

int lexer(char *input, t_list **token_list)
{
	size_t i;
	size_t length;
	t_token_type type;
	t_token *token;
	t_list *new_tok;
	i = 0;
	(void)token_list;
	while (input[i])
	{
		length = 0;
		if (!is_space(input[i]))
		{
			type = scan_for_token_type(input + i, &length);
			if (type == TK_ERROR)
			{
				printf("Error: Scanning for token type\n");
				token = NULL;
			}
			else
			{
				token = create_token(type, input + i, length);
				new_tok = ft_lstnew((void *)token);
				ft_lstadd_back(token_list, new_tok);
			}
		}
		else
			length++;
		i += length;
	}
	return (EXIT_SUCCESS);
}

static int get_argv_amount(t_list *token_list)
{
    t_list  *current = token_list;
    t_token *token;
    int     arg_amount = 0;

    while (current)
    {
        if (!current->content)
            break;
        token = (t_token *)current->content;
        if (!token || !token->value)
            break;
        if (token->type != TK_WORD && token->type != TK_DOUBLE_QUOTE)
            break;
        arg_amount++;
        current = current->next;
    }
    return (arg_amount);
}


int parser(t_list *token_list, t_list **cmd_list)
{
    t_list  *current = token_list;
    t_token *token;
    t_cmd   cmd;
    int     arg_amount;

    while (current)
    {
        arg_amount = get_argv_amount(current);
        printf("[DEBUG] arg_amount = %d\n", arg_amount);
        if (arg_amount <= 0)
        {
            current = current->next;
            continue;
        }

        cmd.argv = malloc(sizeof(char *) * (arg_amount + 1));
        if (!cmd.argv)
            return (EXIT_FAILURE);

        int i = 0;
        while (i < arg_amount && current)
        {
            token = (t_token *)current->content;
            if (!token || !token->value)
            {
                printf("[DEBUG] NULL token at i=%d\n", i);
                break;
            }
            printf("[DEBUG] token->value = %s\n", token->value);
            cmd.argv[i] = ft_strdup(token->value);
            current = current->next;
            i++;
        }
        cmd.argv[i] = NULL;

        t_cmd *new_cmd = malloc(sizeof(t_cmd));
		if (!new_cmd)
			return (EXIT_FAILURE);
        new_cmd->argv = cmd.argv;
        t_list *new = ft_lstnew(new_cmd);
		if (!new)
			return (EXIT_FAILURE);
        ft_lstadd_back(cmd_list, new);
    }
    return (EXIT_SUCCESS);
}
