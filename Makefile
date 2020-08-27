CFLAGS = -Wall -Wextra -Werror

NAME = minishell
INCLUDE  = include/
SRCS =  main.c \
		GNL/get_next_line.c \
		GNL/get_next_line_utils.c \
		shell_loop/shell_loop.c \
		shell_loop/execute.c \
		shell_loop/export.c \
		shell_loop/unset.c \
		shell_loop/enviroment_utils.c \
		shell_loop/enviroment_utils2.c \
		shell_loop/handler.c \
		shell_loop/echo.c \
		shell_loop/parse_function.c \
		shell_loop/pipe_dup.c \
		shell_loop/launch.c \
		parser/free.c \
		parser/list_utils.c \
		parser/parse_quotes.c \
		parser/parse_slash.c \
		parser/parse_spec.c \
		parser/parser_lists.c \
		parser/parser_lists_2.c \
		parser/parsing.c \
		parser/redirection_list.c \
		parser/redirections.c \
		parser/redirections_2.c \
		parser/shell_split.c \
		parser/shell_split_utils.c \
		parser/split_nodes.c \
		parser/split_nodes_utils.c \

OBJS = $(SRCS:.c=.o)

LIB = -Llibft -lft

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	make -C libft/
	gcc -I $(INCLUDE) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)

%.o: %.c
	gcc -I $(INCLUDE) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all