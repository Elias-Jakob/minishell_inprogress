#ifndef LEXER_H
# define LEXER_H

#include "includes.h"

typedef enum e_token_type
{
	TK_WORD,
	TK_PIPE,
	TK_REDIRECT_IN,
	TK_REDIRECT_OUT,
	TK_APPEND_OUT,
	TK_SINGLE_QUOTE,
	TK_DOUBLE_QUOTE,
	TK_HEREDOC,
	TK_ENV,
	TK_ERROR
}	t_token_type;

typedef struct	s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

int				is_space(char c);
char			*ft_strndup(const char *s1, size_t n);

t_token_type	scan_for_quotes(char *input, size_t *length);
t_token_type	scan_for_word(char *input, size_t *length);
t_token_type	scan_for_env(char *input, size_t *length);
t_token_type	scan_for_redirect(char *input, size_t *length);
t_token_type	scan_for_token_type(char *input, size_t *length);

int				lexer(char *input, t_list **token_list);

#endif
