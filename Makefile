CFLAGS = -Wall -Wextra -Werror

NAME = lsh

SRCS =  main.c \
		GNL/get_next_line.c \
		GNL/get_next_line_utils.c \
		list_utils.c \
		shell_loop.c \
		helper.c \
		execute.c \
		export.c \
		unset.c \
		enviroment_utils.c \
		utils.c \
		handler.c \
		parser/redirection_parser.c \
		parser/redirection_parser_utils.c \
		parser/environment_parser.c \
		parser/shell_split_2.c \
		parser/shell_split_utils.c \
		parser/shell_split_utils_2.c \
		parser/str_utils.c \
		parser/shell_split.c

OBJS = $(SRCS:.c=.o)

LIB = -Llibft -lft

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft/
	gcc $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all