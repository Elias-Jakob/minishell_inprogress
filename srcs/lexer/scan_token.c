#include "../../includes/minishell.h"

char	*expand_env_var(char *input, size_t dollar_pos, char **env)
{
	char	*var_name;
	char	*var_value;
	char	*before_var;
	char	*after_var;
	char	*result;
	size_t	var_len;
	size_t	i;

	i = dollar_pos + 1;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
	var_len = i - dollar_pos - 1;
	if (var_len == 0)
		return (ft_strdup(input));
	var_name = ft_calloc(sizeof(char), var_len + 1);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, input + dollar_pos + 1, var_len + 1);
	var_value = get_env_value(env, var_name);
	if (!var_value)
		var_value = "";
	before_var = ft_calloc(sizeof(char), dollar_pos + 1);
	if (!before_var)
		return (free(var_name), NULL);
	ft_strlcpy(before_var, input, dollar_pos + 1);
	after_var = input + dollar_pos + 1 + var_len;
	result = ft_calloc(sizeof(char),
		ft_strlen(before_var) + ft_strlen(var_value) + ft_strlen(after_var) + 1);
	if (!result)
		return (free(var_name), free(before_var), NULL);
	ft_strlcpy(result, before_var, ft_strlen(before_var) + 1);
	ft_strlcat(result, var_value, ft_strlen(before_var) + ft_strlen(var_value) + 1);
	ft_strlcat(result, after_var,
		ft_strlen(before_var) + ft_strlen(var_value) + ft_strlen(after_var) + 1);
	free(var_name);
	free(before_var);
	return (result);
}

t_token_type	scan_for_quotes(char *input, size_t *length, char **env)
{
	char	*expanded;
	size_t	i;

	if (*input == '"')
	{
		expanded = ft_strdup(input);
		if (!expanded)
			return (TK_ERROR);
		i = 1;
		while (expanded[i] && expanded[i] != '"')
		{
			if (expanded[i] == '$')
			{
				char *new_expanded = expand_env_var(expanded, i, env);
				if (new_expanded)
				{
					free(expanded);
					expanded = new_expanded;
				}
			}
			i++;
		}
		i = 1;
		while (expanded[i] && expanded[i] != '"')
			i++;
		if (expanded[i] == '"')
		{
			*length = i + 1;
			ft_strlcpy(input, expanded, *length + 1);
			free(expanded);
			return (TK_DOUBLE_QUOTE);
		}
		free(expanded);
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

static	int	is_char_redir(char c)
{
	return (c == '|' || c == '<' || c == '>');
}


t_token_type	scan_for_word(char *input, size_t *length)
{
	while (input[*length])
	{
		(*length)++;
		if (is_space(input[*length]) || input[*length] == '\0'
			|| is_char_redir(input[*length]))
			return (TK_WORD);
	}
	return (TK_ERROR);
}

t_token_type	scan_for_env(char *input, size_t *length)
{
	(*length)++;
	while (ft_isalpha(input[*length]))
		(*length)++;
	return (TK_ENV);
}

t_token_type	scan_for_redirect(char *input, size_t *length)
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

t_token_type	scan_for_token_type(char *input, size_t *length, char **env)
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
		return (scan_for_quotes(input, length, env));
	return (scan_for_word(input, length));
}
