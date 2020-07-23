cmake_minimum_required(VERSION 3.16)
project(Cub C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
link_directories( ~/Desktop/minishell/libft/)
add_executable(minishell main.c
        GNL/get_next_line.c
        GNL/get_next_line_utils.c shell_loop.c minishell.h libft/ft_strcmp.c parser.c list_utils.c helper.c str_utils.c)
target_link_libraries(minishell ft)


