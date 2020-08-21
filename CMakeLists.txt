cmake_minimum_required(VERSION 3.16)
project(Cub C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
link_directories( /Users/ccarl/Desktop/Minishell/libft)
add_executable(minishell main.c
        GNL/get_next_line.c
        GNL/get_next_line_utils.c shell_loop.c minishell.h libft/ft_strcmp.c list_utils.c helper.c parser/str_utils.c parser/shell_split.c execute.c
        unset.c export.c enviroment_utils.c handler.c parser/redirection_parser.c parser/redirection_parser_utils.c parser/environment_parser.c parser/shell_split_2.c parser/shell_split_utils.c parser/shell_split_utils_2.c)
target_link_libraries(minishell ft)


