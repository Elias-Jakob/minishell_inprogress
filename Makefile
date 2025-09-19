NAME = minishell

LEXER = srcs/lexer/utils.c srcs/lexer/scan_token.c srcs/lexer/token_factory.c \
		srcs/lexer/scanner_quotes.c srcs/lexer/scanner_env.c \
		srcs/lexer/scanner_redirect.c srcs/lexer/scanner_operators.c \
		srcs/lexer/scanner_words.c srcs/lexer/lex_input.c srcs/lexer/lexer.c

PARSER = srcs/parser/core/parser_core.c \
		 srcs/parser/validation/validation_token.c \
		 srcs/parser/validation/validation_pipe_and_redir.c \
		 srcs/parser/expansion/expansion.c \
		 srcs/parser/expansion/expansion_env_var.c \
		 srcs/parser/expansion/variable_parser.c \
		 srcs/parser/expansion/variable_resolver.c \
		 srcs/parser/expansion/string_builder.c \
		 srcs/parser/processors/word_processor.c \
		 srcs/parser/processors/pipe_processor.c \
		 srcs/parser/processors/redirection_processor.c \
		 srcs/parser/factories/command_factory.c \
		 srcs/parser/factories/redirection_factory.c \
		 srcs/parser/legacy_files/heredoc.c \
		 srcs/parser/legacy_files/management_command.c \
		 srcs/parser/legacy_files/management_token.c \
		 srcs/parser/legacy_files/redirection_handlers.c

EXECUTER = srcs/execution/execution.c srcs/execution/execute_commands.c srcs/execution/redirect.c \
					 srcs/execution/find_executable.c

ENV = srcs/env/env.c srcs/env/utils.c

BUILTINS = srcs/builtins/ft_echo.c srcs/builtins/ft_cd.c srcs/builtins/ft_pwd.c srcs/builtins/ft_export.c \
					 srcs/builtins/ft_unset.c srcs/builtins/ft_env.c srcs/builtins/ft_exit.c

UTILS = srcs/utils/clean_up.c srcs/utils/error_utils.c srcs/utils/init_shell.c \
				srcs/utils/signals.c

SRCS = srcs/bby_shell.c \
	   $(LEXER)\
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
