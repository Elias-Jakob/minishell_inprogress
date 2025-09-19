NAME = minishell
LEXER = srcs/lexer
PARSER = srcs/parser/parser.c srcs/parser/heredoc.c srcs/parser/management_command.c srcs/parser/management_token.c srcs/parser/redirection_handlers.c srcs/parser/token_processing.c srcs/parser/utils.c
EXECUTER = srcs/execution/execution.c srcs/execution/execute_commands.c srcs/execution/redirect.c \
					 srcs/execution/find_executable.c
ENV = srcs/env/env.c srcs/env/utils.c
BUILTINS = srcs/builtins/ft_echo.c srcs/builtins/ft_cd.c srcs/builtins/ft_pwd.c srcs/builtins/ft_export.c \
					 srcs/builtins/ft_unset.c srcs/builtins/ft_env.c srcs/builtins/ft_exit.c
UTILS = srcs/utils/clean_up.c srcs/utils/error_utils.c srcs/utils/init_shell.c \
				srcs/utils/signals.c
SRCS = srcs/bby_shell.c \
	   $(LEXER)/utils.c $(LEXER)/scan_token.c $(LEXER)/lexer.c\
	   $(PARSER)\
	   srcs/utils/debug_lexer_parser.c\
	   $(EXECUTER) $(BUILTINS) $(UTILS)\
	   $(ENV)
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
