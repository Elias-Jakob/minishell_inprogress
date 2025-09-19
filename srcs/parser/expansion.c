#include "../../includes/parser.h"
#include "../../includes/env.h"

char	*expand_env_var(char *input, size_t dollar_pos, char **env, int last_exit_status)
{
	char	*var_name;
	char	*var_value;
	char	*before_var;
	char	*after_var;
	char	*result;
	int		is_in_bracket;
	size_t	var_len;
	size_t	i;

	is_in_bracket = 0;
	i = dollar_pos + 1;
	if (input[dollar_pos + 1] == '?')
	{
		i = dollar_pos + 2;
		var_len = 1;
	}
	else
	{
		if (input[i] == '{')
		{
			i++;
			is_in_bracket = 1;
		}
		while (input[i] && (ft_isalnum(input[i]) || input[i] == '_' || ft_isdigit(input[i])))
			i++;
		if (is_in_bracket)
			var_len = i - dollar_pos - 2;
		else
			var_len = i - dollar_pos - 1;
	}
	if (var_len == 0)
		return (ft_strdup(input));
	var_name = ft_calloc(sizeof(char), var_len + 1);
	if (!var_name)
		return (NULL);
	if (is_in_bracket)
		ft_strlcpy(var_name, input + dollar_pos + 2, var_len + 1);
	else
		ft_strlcpy(var_name, input + dollar_pos + 1, var_len + 1);
	if (ft_strncmp(var_name, "?", 1) == 0)
		var_value = ft_itoa(last_exit_status);
	else
	{
		var_value = get_env_value(env, var_name);
		if (!var_value)
			var_value = "";
	}
	before_var = ft_calloc(sizeof(char), dollar_pos + 1);
	if (!before_var)
		return (free(var_name), NULL);
	ft_strlcpy(before_var, input, dollar_pos + 1);
	if (is_in_bracket)
		after_var = input + i + 1;
	else
		after_var = input + i;
	result = ft_calloc(sizeof(char),
		ft_strlen(before_var) + ft_strlen(var_value) + ft_strlen(after_var) + 1);
	if (!result)
		return (free(var_name), free(before_var), NULL);
	ft_strlcpy(result, before_var, ft_strlen(before_var) + 1);
	ft_strlcat(result, var_value, ft_strlen(before_var) + ft_strlen(var_value) + 1);
	ft_strlcat(result, after_var,
		ft_strlen(before_var) + ft_strlen(var_value) + ft_strlen(after_var) + 1);
	if (ft_strncmp(var_name, "?", 1) == 0)
		free(var_value);
	free(var_name);
	free(before_var);
	return (result);
}

char	*expand_variables_in_token(char *token_value, char **env, int last_exit_status)
{
	char	*result;
	char	*temp;
	size_t	i;

	if (!token_value)
		return (NULL);
	result = ft_strdup(token_value);
	if (!result)
		return (NULL);
	i = 0;
	while (result[i])
	{
		if (result[i] == '$')
		{
			temp = expand_env_var(result, i, env, last_exit_status);
			if (temp)
			{
				free(result);
				result = temp;
				i = 0;
				continue;
			}
			else
			{
				free(result);
				return (NULL);
			}
		}
		i++;
	}
	return (result);
}

char	*process_token_expansion(t_token *token, char **env, int last_exit_status)
{

	if (!token || !token->value)
		return (NULL);
	if (token->type == TK_SINGLE_QUOTE)
		return (ft_strdup(token->value));
	if (token->type == TK_DOUBLE_QUOTE)
		return (expand_variables_in_token(token->value, env, last_exit_status));
	if (token->type == TK_ENV || token->type == TK_WORD)
		return (expand_variables_in_token(token->value, env, last_exit_status));
	return (ft_strdup(token->value));
}
