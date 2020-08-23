CFLAGS = -Wall -Wextra -Werror

NAME = lsh
INCLUDE  = include/
SRCS =  main.c \
		GNL/get_next_line.c \
		GNL/get_next_line_utils.c \
		parser/list_utils.c \
		shell_loop/shell_loop.c \
		shell_loop/execute.c \
		shell_loop/export.c \
		shell_loop/unset.c \
		shell_loop/enviroment_utils.c \
		shell_loop/enviroment_utils2.c \
		shell_loop/handler.c \
		shell_loop/parse_function.c \
		shell_loop/pipe_dup.c \
		shell_loop/launch.c \
		parser/redirection_list.c \
		parser/redirection_parser.c \
		parser/redirection_parser_utils.c \
		parser/environment_parser.c \
		parser/shell_split.c \
		parser/shell_split_2.c \
		parser/shell_split_utils.c \
		parser/shell_split_utils_2.c \
		parser/str_utils.c \


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