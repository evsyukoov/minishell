CFLAGS = -Wall -Wextra -Werror

NAME = lsh

SRCS =  main.c \
		GNL/get_next_line.c \
		GNL/get_next_line_utils.c \
		str_utils.c \
		list_utils.c \
		shell_loop.c \
		helper.c \
		execute.c \
		shell_split.c \
		export.c \
		unset.c \
		enviroment_utils.c \
		utils.c \
		parse_function.c \
		handler.c

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