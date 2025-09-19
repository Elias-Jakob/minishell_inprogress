#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "libft.h"
# include "enums.h"
# include "structs.h"

int				is_space(char c);
char			*ft_strndup(const char *s1, size_t n);

// token_factory.c
t_token			*create_token(t_token_type type, char *input, size_t length);
void			destroy_token(t_token *token);

t_token_type	scan_for_operators(char *input, size_t *length);
t_token_type	scan_for_quotes(char *input, size_t *length);
t_token_type	scan_for_word(char *input, size_t *length);
t_token_type	scan_for_env(char *input, size_t *length);
t_token_type	scan_for_redirect(char *input, size_t *length);
t_token_type	scan_for_token_type(char *input, size_t *length);

int				lex_input(char *input, size_t *i, t_list **token_list);
int				lexer(char *input, t_list **token_list);

#endif
