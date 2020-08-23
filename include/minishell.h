/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 21:06:34 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/23 19:52:47 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# define NONE -1
# define REWRITE 0
# define WRITE 1
# define REVERSE 2
# define COMMAND 0
# define PIPE 1
# include "libft.h"
# include <zconf.h>
# include <stdio.h>
# include "get_next_line.h"
# include <string.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct 		s_names
{
	char 			*name;
	int 			type;
	struct s_names  *next;
}					t_files;

typedef struct 		s_args
{
	char 			**args;
	int 			flag;
	t_files 		*files;
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

char			**env_copy;
pid_t			g_lsh_child;
int				g_last_code;
int				g_flag;

void			shell_loop(char *envp[]);
int				cd(char **argv, char *envp[]);
void			push(t_args **lst, t_args *new);
void			print_arg_list(t_args *lst);
char			**shell_split(char *arg, char **env);
t_args 		*create_new_node(char **s, int g_flag, t_files *files);
void			free_arguments(char ***argv);
void			print_argv(char **argv);
t_args			*create_list(char *arg, char **env);
int				execute(char **argv, char *envp[]);
int				str_endswith(char *s, char *set);
t_args			*parse_redirections(t_args *lst);
char			*get_env_var(char *name, char *envp[]);
char			**realloc_env(char *envp[]);
int				env_len(char *envp[]);
int				env_strcmp(char *name, char *env_var);
int				print_env(char *envp[], char **argv);
char			**realloc_env(char *envp[]);
char			*joinenv(char *name, char *value);
int				unset(char *name, char *envp[]);
char			*read_fd(int fd);
char			**rewrite_args(char **argv, char *new_arg);
int				execution(char **argv, char **envp[]);
void			signal_listener(int signal_num);
void			listener(int signal_num);
int				print_error_log(char *lsh, char *command,
char *argument, char *msg);
int				export(char *arg, char **envp[]);
int				str_startswith(char *s, char *set);
void			nothing(int signal_num);
void			free_args_list(t_args **lst);
void			*parse_syntax_error();
void			skip(char **s, char del);
char			**case1(char **argv, int arg_index);
char			**case2(char **argv, int arg_index, size_t len);
int				last_arg_len(char *arg, char redirection_type);
char			*find_file_name(char *arg);
char			*replace_bash_symbols(char ***arg, char **env);
int				env_len2(char *arg);
char			*init_env_name(char *arg);
char			*get_begin_string(char *current_ptr, int len);
int				quotes_size(char *arg);
char			*join_char(char *arg, char c);
int				is_dollar_symbol(char *arg);
void			skip_env(char **arg);
char			*init_arg(char **arg, char **env, t_split var);
int				arguments_counter(char *s);
char			quote_type(char *arg);
int				argument_len(char *s, char quote);
void			sighandler(int sig_num);
int				free_list(char **all_path);
int				free_all(char **all_path, char *path);
int				exe_one_command(t_args *args_lst, char **envp[]);
int				print_error_log(char *lsh, char *command,
char *argument, char *msg);
int				launch(char **argv, char *envp[]);
char			*init_home_path(char *tilda, char **arg);
t_files			*new_redirection(char *file_path, int file_option);
void			push_redirect(t_files **lst, t_files *new);
char			**get_commands(char **argv, int arg_index);
t_files			*new_redirection(char *file_path, int file_option);

#endif
