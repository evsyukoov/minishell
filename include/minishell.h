/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 21:06:34 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/28 01:02:28 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# define NONE -1
# define REWRITE 1
# define WRITE 2
# define REVERSE 3
# define COMMAND 0
# define PIPE 1
# include "get_next_line.h"
# include "libft.h"
# include <zconf.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct 		s_str
{
	char 			curr;
	char 			*string;
	struct s_str	*next;
}					t_str;

typedef struct 		s_argv
{
	char 			*str;
	struct s_argv	*next;
}					t_node;


typedef struct		s_names
{
	char			*name;
	int				type;
	struct s_names	*next;
}					t_files;

typedef struct		s_args
{
	char			**args;
	int				flag;
	t_files			*files;
	struct s_args	*next;
}					t_args;

typedef struct		s_split
{
	int				args;
	int				i;
	int				j;
	char			q_type;
	int				arg_len;
}					t_split;

char			**g_env_copy;
pid_t			g_lsh_child;
int				g_last_code;

void				shell_loop();
int					cd(char **argv, char *envp[]);
void				push(t_args **lst, t_args *new);
void				print_arg_list(t_args *lst);
t_args				*create_new_node(char **s, int g_flag, t_files *files);
void				*free_arguments(char ***argv);
void				print_argv(char **argv);
t_args				*create_list(char *arg);
int					execute(char **argv);
int					str_endswith(char *s, char *set);
t_args				*parse_redirections(t_args *lst);
char				*get_env_var(char *name, char *envp[]);
char				**realloc_env(char *envp[]);
int					env_len(char *envp[]);
int					env_strcmp(char *name, char *env_var);
int					print_env(char *envp[], char **argv);
char				**realloc_env(char *envp[]);
char				*joinenv(char *name, char *value);
int					unset(char *name, char *envp[]);
char				*read_fd(int fd);
char				**rewrite_args(char **argv, char *new_arg);
int					execution(char **argv, char **envp[]);
void				signal_listener(int signal_num);
void				listener(int signal_num);
int					print_error_log(char *lsh, char *command,
char *argument, char *msg);
int					export(char *arg, char **envp[]);
int					str_startswith(char *s, char *set);
void				nothing(int signal_num);
void				free_args_list(t_args **lst);
void				*parse_syntax_error(int a);
void				skip(char **s, char del);
char				*replace_bash_symbols(char ***arg, char **env);
int					env_len2(char *arg);
char				*init_env_name(char *arg);
char				quote_type(char *arg);
void				sighandler(int sig_num);
int					free_list(char **all_path);
int					free_all(char **all_path, char *path);
int					exe_one_command(t_args *args_lst, char **envp[]);
int					print_error_log(char *lsh, char *command,
char *argument, char *msg);
//int					launch(char **argv, char *envp[]);
char				*init_home_path(char *tilda, char **arg);
t_files				*new_redirection(char *file_path, int file_option);
void				push_redirect(t_files **lst, t_files *new);
char				**get_commands(char **argv, int arg_index);
t_files				*new_redirection(char *file_path, int file_option);
char				*get_environment_with_quotes(char *arg,
char **env, int begin_len);
char				*get_environment_string(char *arg, char **env,
int begin_len);
int					check(t_args *lst);
int					check_error_redirections(char **argv, int i);
void 	print_arg_list(t_args *lst);
char			**split(char *s, char c);
t_args 			*get_node(t_args *lst, int index);
int				word_counter(char *s, char delimetr);
int 			skip_quotes(char **s, char q_type);
int				echo (char *argv[]);
void 			add_to_list(t_node **head, char *str);
void			add_to_str(t_str **head, char c, char *string);
char			*list_to_str(t_str **str);
char			**node_to_argv(t_node **head);
char			**split_arg(char *s, t_files **files);
int				launch(char **argv);
char			*parsing(char *s, t_str **str);
t_str			*get_last_char(t_str *lst);
int 			lst_size(t_str *str);
t_node			*get_last(t_node *node);
int				argv_size(t_node *node);
int				type_of_redirection(char **s);
int				is_redirections(char *s);
char			*wait_for_next_redirect(char *s);
void 			free_files(t_files **files);
char			*parse_redirect(char *s, t_files **files);
void			free_nodes(t_node **head);
int				redirection_parser_loop(char **s, t_files **files, t_str *str, t_node **node);
int 	is_spec_symbols(char *s);
void 	push_envir(char *s, t_str **head);
char 	*parse_dollar(char *s, t_str **head);
char	*parse_home_path(char *s, t_str **head);
void 	parse_double_quotes(t_str **head, char **s);
void 	parse_simple_quotes(t_str **head, char **s);
char 	*analize_slash(char *s, t_str **head, int flag);
int			number_of_arguments(char **argv);
int 		is_pipe(char *s);
int 		is_pipe_end(char *arg);
void 		change_option(t_args *lst);

#endif
