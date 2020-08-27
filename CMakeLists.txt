cmake_minimum_required(VERSION 3.16)
project(Cub C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
link_directories(/Users/ccarl/Desktop/Shell2/libft)
add_executable(main.c
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
        parser/list_utils.c
        parser/split_nodes.c
        parser/redirection_list.c
        parser/shell_split.c
        parser/shell_split_utils.c
        helper.c
        parser/split_nodes.c
        parser/parsing.c
        parser/parser_lists.c
        parser/parser_lists_2.c
        parser/redirections.c
        parser/redirections_2.c
        parser/free.c
        parser/parse_spec.c
        parser/parse_quotes.c
        parser/parse_slash.c
        parser/split_nodes_utils.c)
target_link_libraries(minishell ft)