#include "../../../includes/parser.h"

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
