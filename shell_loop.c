/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:20:27 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/19 01:15:50 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_args *get_argv(char **env)
{
    char *line;
    t_args *lst;

    if (get_next_line(0, &line) < 0)
        return 0;
    if (*line == '\0')
    	return (0);
   	lst = create_list(line, env);
	// print_arg_list(lst);
    return (lst);
}

int exe_one_command(t_args *args_lst, char **envp[])
{
	int fd_out;
	int fd_in;
	int fd;
	char buf[10];
	int n;
	
	fd_out = dup(1);
	fd_in = dup(0);
	if(args_lst->file_option == NONE)
		execution(args_lst->args, envp);
	else if (args_lst->file_option == 2)
	{
			
		if ((fd = open(args_lst->file_path, O_RDONLY)) > 0)
		{
			dup2(fd, 0);
			if (args_lst->args[0][0])
				execution(args_lst->args, envp);
			else
				while((n = read(0, buf, 10)) > 0)
					write(1, buf, n);
			close(fd);	
			dup2(fd_in, 0);
		}
	}
	else
	{
		if	(args_lst->file_option)
			fd = open(args_lst->file_path, O_RDWR | O_APPEND | O_CREAT, 00644);
		else
			fd = open(args_lst->file_path, O_RDWR | O_TRUNC | O_CREAT, 00644);
		dup2(fd, 1);
		execution(args_lst->args, envp);
		close(fd);
		dup2(fd_out, 1);
	}
	return(0);
}

int parse_str(t_args *args_lst, char **envp[])
{

	int fd_buf[2];
	pid_t child;
	int fd_in;
	int status;
	
	fd_in = dup(0);

	while(args_lst)
	{
		pipe(fd_buf);
		if( args_lst->flag == COMMAND)
		{
			exe_one_command(args_lst, envp);
			args_lst = args_lst->next;
			dup2(fd_in, 0);
		}
		else if (args_lst->flag == PIPE)
		{

			if (!(child = fork())){
				dup2 (fd_buf[1], 1);
				close(fd_buf[0]);
				exe_one_command(args_lst, envp);
				exit(0);
			}
			else{
				waitpid(child, &status, WUNTRACED);
				args_lst = args_lst->next;
				dup2 (fd_buf[0], 0);
				close(fd_buf[1]);
   			}
		}
	}
	return(1);
}

void    shell_loop(char *envp[])
{
	int status;
    t_args *args_lst;

    status = 1;
    while (1)
   	{
		write(1, "minishell : ", 12);
		args_lst = get_argv(envp);
		if (args_lst)
			status = parse_str(args_lst, &envp);
		if (!status)
			break ;
   }
}

