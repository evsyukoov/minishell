cmake_minimum_required(VERSION 3.16)
project(Cub C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
link_directories(/Users/ccarl/Desktop/Minishell2/minishell/libft)
add_executable(minishell main.c
        GNL/get_next_line.c
        GNL/get_next_line_utils.c
        shell_loop/enviroment_utils.c
        shell_loop/enviroment_utils2.c
        shell_loop/execute.c
        shell_loop/export.c
        shell_loop/handler.c
        shell_loop/launch.c
        shell_loop/parse_function.c
        shell_loop/pipe_dup.c
        shell_loop/shell_loop.c
        shell_loop/unset.c
        libft/ft_strcmp.c
        parser/environment_parser.c
        parser/list_utils.c
        parser/str_utils.c
        parser/redirection_list.c
        parser/redirection_parser.c
        parser/redirection_parser_utils.c
        parser/shell_split.c
        parser/shell_split_2.c
        parser/shell_split_utils.c
        parser/shell_split_utils_2.c)
target_link_libraries(minishell ft)


