NAME = minishell
LEXER = srcs/lexer
PARSER = srcs/parser
EXECUTER = srcs/execution
BUILTINS = srcs/builtins/ft_echo.c srcs/builtins/ft_cd.c srcs/builtins/ft_pwd.c \
					 srcs/builtins/ft_export.c srcs/builtins/ft_unset.c srcs/builtins/ft_env.c \
					 srcs/builtins/ft_exit.c
UTILS = srcs/utils
SRCS = srcs/bby_shell.c \
	   $(LEXER)/utils.c $(LEXER)/scan_token.c $(LEXER)/lexer.c\
	   $(PARSER)/utils.c $(PARSER)/parse_redirection.c srcs/new_parser/parser.c\
	   srcs/utils/debug_lexer_parser.c\
	   $(EXECUTER)/execute.c $(EXECUTER)/execute_commands.c\
	   $(EXECUTER)/redirect.c $(EXECUTER)/find_executable.c\
	   $(BUILTINS) \
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
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all
