//
// Created by Casie Carl on 7/21/20.
//

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "libft/libft.h"
# include <zconf.h>
# include <stdio.h>
# include "GNL/get_next_line.h"
# include <string.h>

# define BUILTINS 7
# define ECHO 0
# define CD 1
# define PWD 2
# define EXPORT 3
# define UNSET 4
# define ENV 5
# define EXIT 6

void    shell_loop();
int     cd(char **argv);


#endif //CUB_MINISHELL_H
