#include "../../includes/minishell.h"

int	is_word_boundary(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\0');
}

int	is_operator_boundary(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_token_boundary(char c)
{
	return (is_word_boundary(c) || is_operator_boundary(c));
}