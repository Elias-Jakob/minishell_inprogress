#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "libft.h"
# include "enums.h"
# include "structs.h"

int				is_space(char c);
char			*ft_strndup(const char *s1, size_t n);

	t_token_type	scan_for_quotes(char *input, size_t *length, char **env, int last_exit_status);
t_token_type	scan_for_word(char *input, size_t *length);
t_token_type	scan_for_env(char *input, size_t *length);
t_token_type	scan_for_redirect(char *input, size_t *length);
t_token_type	scan_for_token_type(char *input, size_t *length, char **env, int last_exit_status);

int				lexer(char *input, t_list **token_list, char **env, int last_exit_status);

#endif
