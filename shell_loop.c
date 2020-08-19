/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:20:27 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/19 19:27:46 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <sys/types.h>

int		launch(char **argv, char *envp[])
{
	int  status;
	
	child = fork();
	if (child < 0)
		perror("minishell");
	else if (child == 0)
	{
		//signal(SIGQUIT, &listener_ctrl_d);
		if (execute(argv, envp) == -1) {
			perror("command not found");
			return (1);
		}
	} 
	else
	{
		//wait(&status);
		//if (WIFSIGNALED(status))
		//	return WTERMSIG(status) + 256;  //пытался достать код ошибки,безрезультатно
		//return WEXITSTATUS(status);
		waitpid(child, &status, WUNTRACED);
		while (WIFEXITED(status) == 0)
			waitpid(child, &status, WUNTRACED);
	}
	return (1);
}

//SIGQUIT - ctrl - \
//SIGINT  - ctrl - C


int     cd(char **argv)
{
	if (chdir(argv[1]) != 0)
    	perror(argv[1]);
    return (1);
}

void	free_arguments(char ***argv)
{
	int i;

	i = 0;
	if (*argv) {
		while ((*argv)[i])
			free((*argv)[i++]);
		free(*argv);
	}
}

int    execution(char **argv, char **envp[])
{
	char wd[256];

	//printf("errno = %d\n", errno);
	if (ft_strcmp(argv[0], "cd") == 0)
		return (cd(argv));
	else if(ft_strcmp(argv[0], "pwd") == 0) {
		ft_putendl_fd(getwd(wd), 1);
		return (1);
	}
	else if (ft_strcmp(argv[0], "unset") == 0)
		return(unset(argv[1], *envp));
	else if (ft_strcmp(argv[0], "env") == 0)
		return(print_env(*envp));
	else if (ft_strcmp(argv[0], "export") == 0)
		return(export(argv[1], envp));
	else if (ft_strcmp(argv[0], "exit") == 0)
		exit(0);
	return (launch(argv, *envp));
}

t_args *get_argv(char **env)
{
	char *line;
	t_args *lst;

	int ret = get_next_line(0, &line);
	if (ret < 0)
		return (0);
	if (ret == 0)
	{
		kill(shell_pid, SIGTERM);
		exit(0);
	}
	if (*line == '\0')
		return (0);
	lst = create_list(line, env);
	// print_arg_list(lst);
	return (lst);
}

int parse_str(t_args *args_lst, char **envp[])
{
	int fd_out;
	int fd_in;
	int fd;
	
	fd_out = dup(1);
	fd_in = dup(0);
	while(args_lst)
	{
		if( args_lst->flag == COMMAND)
		{
			if(args_lst->file_option == NONE)
				execution(args_lst->args, envp);
			else if (args_lst->file_option == 2)
			{
				if ((fd = open(args_lst->file_path, O_RDONLY)) > 0)
				{
					dup2(fd, 0);				
					execution(args_lst->args, envp);
					close(fd);	
					dup2(fd_in, 0);
				}
			}
			else
			{
				if(args_lst->file_option == REWRITE)
					fd = open(args_lst->file_path, O_RDWR | O_TRUNC | O_CREAT, 00644);
				else if	(args_lst->file_option == WRITE)
					fd = open(args_lst->file_path, O_RDWR | O_APPEND | O_CREAT, 00644);
				dup2(fd, 1);
				execution(args_lst->args, envp);
				close(fd);
				dup2(fd_out, 1);
			}
			args_lst = args_lst->next;
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

