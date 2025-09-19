#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

// # include <termios.h>

# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"

# include "enums.h"
# include "structs.h"

# include "env.h"
# include "parser.h"
# include "lexer.h"

# include "execution.h"
# include "utils.h"
// ------------------- DEBUGING --------------------- //
void debug_lexer(t_list *token_list, const char *input);
void debug_parser(t_cmd *cmd_head, const char *input);
void debug_lexer_and_parser(t_list *token_list, t_cmd *cmd_head, const char *input);
void debug_input(const char *test_input);

#endif
