NAME = minishell
SRCS = srcs/bby_shell.c srcs/lexer/lexer.c srcs/parser/parser.c #srcs/execution/execute.c srcs/execution/pipeline.c srcs/execution/redirect.c srcs/utils/clean_up.c
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
