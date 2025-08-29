#include "../../includes/minishell.h"

static int	is_space(char c)
{
		return ((c >= 9 && c <= 13) || c == 32);
}

static t_token_type	scan_for_token_type(char *input, size_t *length)
{
		(*length)++;
		if (ft_isalpha(*input))
		{
				while (ft_isalpha(input[*length]))
						(*length)++;
				return (TK_WORD);
		}
		if (*input == '|')
				return (TK_PIPE);
		if (*input == '<')
		{
				if (*(input + 1) == '<')
				{
						(*length)++;
						return (TK_HEREDOC);
				}
				return (TK_REDIRECT_IN);
		}
		if (*input == '>')
		{
				if (*(input + 1) == '>')
				{
						(*length)++;
						return (TK_APPEND_OUT);
				}
				return (TK_REDIRECT_OUT);
		}
		if (*input == '$')
				return (TK_ENV);
		if (*input == '"')
				return (TK_DOUBLE_QUOTE);
		if (*input == '\'')
				return (TK_SINGLE_QUOTE);
		(*length)--;
		return (TK_ERROR);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*s2;
	size_t	i;

	i = 0;
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

static t_token	*create_token(t_token_type type, char *input, size_t length)
{
		t_token	*token;

		token = malloc(sizeof(t_token));
		if (!token)
				return (NULL);
		token->type = type;
		token->value = ft_strndup(input, length);
		return (token);
}

int	lexer(char *input, t_list **token_list)
{
		size_t			i;
		size_t			length;
		t_token_type	type;
		t_token			*token;
		t_list			*new_tok;
		i = 0;
		(void)token_list;
		while (input[i])
		{
				length = 0;
				if (!is_space(input[i]))
				{
						type = scan_for_token_type(input + i, &length);
						token = create_token(type, input + i, length);
						new_tok = ft_lstnew((void *)token);
						ft_lstadd_back(token_list, new_tok);
				}
				else
						length++;
				i += length;
		}
		return (EXIT_SUCCESS);
}
