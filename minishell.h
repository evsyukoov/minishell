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

//flag - отвечает за то, что идет после ноды(; - COMMAND, | - PIPE)
//file_option - отвечает за тип редирекшна (> - REWRITE >> - WRITE)

typedef struct 		s_args
{
	char 			**args;
	int 			flag;
	char 			*file_path;
	int				file_option;
	struct s_args	*next;
}					t_args;


typedef struct 		s_split
{
	int 			args;
	int 			i;
	int 			j;
	char 			q_type;
	int 			arg_len;
}					t_split;
# define COMMAND 0
# define PIPE 1
# define NONE -1

# define REWRITE 0
# define WRITE 1

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
char	**shell_split(char *arg);
t_args 		*create_new_node(char **s, int flag, char *file_path, int file_option);
void	free_arguments(char ***argv);
void 	print_argv(char **argv);
t_args 	*create_list(char *arg);
int execute(char **argv, char *envp[]);
int		str_endswith(char *s, char *set);
t_args 	*parse_redirections(t_args *lst);


#endif //CUB_MINISHELL_H
