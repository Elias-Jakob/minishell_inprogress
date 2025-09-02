NAME = minishell
LEXER = srcs/lexer
PARSER = srcs/parser
SRCS = srcs/bby_shell.c \
	   $(LEXER)/utils.c $(LEXER)/scan_token.c $(LEXER)/lexer.c\
	   $(PARSER)/utils.c $(PARSER)/parse_redirection.c $(PARSER)/parser.c\
	   srcs/utils/debug_lexer_parser.c\
	   srcs/execution/execute.c srcs/execution/execute_commands.c\
	   srcs/execution/redirect.c srcs/utils/clean_up.c srcs/utils/error_utils.c
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
