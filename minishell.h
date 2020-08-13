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
# include <sys/types.h>

typedef struct 		s_args
{
	char 			**args;
	int 			flag;
	char 			*redirection_path;
	struct s_args	*next;
}					t_args;

# define COMMAND 0
# define PIPE 1

# define BUILTINS 7
# define ECHO 0
# define CD 1
# define PWD 2
# define EXPORT 3
# define UNSET 4
# define ENV 5
# define EXIT 6

void    shell_loop(char *envp[]);
int     cd(char **argv);
void	push(t_args **lst, t_args *new);
void 	print_arg_list(t_args *lst);
t_args		*create_list(char *line);
int		str_endswith(char *s, char *set);
int		str_startswith(char *s, char *set);
t_args	*shell_split(char const *s, char del1, char del2);
char 		**split_commands(char *line);
t_args 		*create_new_node(char **s, int flag);
char	*shell_join(char const *s1, char const *s2);


#endif //CUB_MINISHELL_H
