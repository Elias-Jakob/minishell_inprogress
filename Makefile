NAME = minishell
LEXER = srcs/lexer
PARSER = srcs/parser
EXECUTER = srcs/execution/execute.c srcs/execution/execute_commands.c srcs/execution/redirect.c \
					 srcs/execution/find_executable.c srcs/execution/init_context.c
BUILTINS = srcs/builtins/ft_echo.c srcs/builtins/ft_cd.c srcs/builtins/ft_pwd.c srcs/builtins/ft_exit.c
UTILS = srcs/utils
SRCS = srcs/bby_shell.c \
	   $(LEXER)/utils.c $(LEXER)/scan_token.c $(LEXER)/lexer.c\
	   srcs/new_parser/parser.c\
	   srcs/utils/debug_lexer_parser.c\
	   $(EXECUTER) $(BUILTINS)\
	   $(UTILS)/clean_up.c $(UTILS)/error_utils.c
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = libft
LIBFT = libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
DEBUG_FLAGS = -g

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)

$(LIBFT):
	@make bonus -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all
