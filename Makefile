NAME = minishell
LEXER = srcs/lexer
PARSER = srcs/parser
EXECUTER = srcs/execution
BUILTINS = srcs/builtins
UTILS = srcs/utils
SRCS = srcs/bby_shell.c \
	   $(LEXER)/utils.c $(LEXER)/scan_token.c $(LEXER)/lexer.c\
	   $(PARSER)/utils.c $(PARSER)/parse_redirection.c $(PARSER)/parser.c\
	   $(EXECUTER)/execute.c $(EXECUTER)/execute_commands.c\
	   $(EXECUTER)/redirect.c $(EXECUTER)/find_executable.c\
		 $(BUILTINS)/ft_echo.c \
		 $(UTILS)/clean_up.c $(UTILS)/error_utils.c
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = libft
LIBFT = libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
DEBUG_FLAGS = -g

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)

$(LIBFT):
	@make bonus -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
