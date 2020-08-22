/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:20:27 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/22 21:55:40 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <sys/types.h>

/*int		launch(char **argv, char *envp[])
{
	int  status;
	flag = 1;
	status = 0;
	lsh_child = fork();
	if (lsh_child < 0)
		perror("minishell");
	else if (lsh_child == 0)
	{
		if (execute(argv, envp) == -1) {
			print_error_log("lsh: ", NULL, argv[0], "command not found");
			exit(127);
		}
	} 
	else
	{
		signal(SIGQUIT, listener);
		signal(SIGINT, listener);
		waitpid(lsh_child, &status, WUNTRACED);
	}
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (WEXITSTATUS(status));		//возвращает код последнего return или exit
}

//SIGQUIT - ctrl - \
//SIGINT  - ctrl - C

int 	print_error_log(char *lsh, char *command, char *argument, char *msg)
{
	if (lsh)
		write(2, "lsh: ", 5);
	if (command)
		write(2, command, ft_strlen(command));
	if (argument) {
		write(2, argument, ft_strlen(argument));
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
}

int     cd(char **argv)
{
	if (chdir(argv[1]) != 0) {
		// print_error_log("lsh: ", "cd: ", argv[1], strerror(errno));
		return (1);
	}
    return (0);
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

int 	is_contains_alpha(char *arg)
{
	while (*arg)
	{
		if (ft_isalpha(*arg))
			return (1);
		arg++;
	}
	return (0);
}

int 	exit_program(char *arg)
{
	write(1, "exit\n", 5);
	if (arg)
	{
		if (is_contains_alpha(arg))
		{
			last_code = 255;
			exit(255);
		}
		else
		{
			last_code = ft_atoi(arg);
			if (last_code > 255)
				exit(0);
			else
				exit(last_code);
		}
	}
	else
		exit(0);
}

int    execution(char **argv, char **envp[])
{
	char wd[256];

	//printf("errno = %d\n", errno);
	if (ft_strcmp(argv[0], "cd") == 0)
		return (cd(argv));
	else if(ft_strcmp(argv[0], "pwd") == 0) {
		ft_putendl_fd(getwd(wd), 1);
		return (0);
	}
	else if (ft_strcmp(argv[0], "unset") == 0)
		return(unset(argv[1], *envp));
	else if (ft_strcmp(argv[0], "env") == 0)
		return(print_env(*envp, argv));
	else if (ft_strcmp(argv[0], "export") == 0)
		return(export(argv[1], envp));
	else if (ft_strcmp(argv[0], "exit") == 0)
		exit_program(argv[1]);
		return (launch(argv, *envp));
}*/

t_args *get_argv(char **env)
{
	char *line;
	t_args *lst;

	int ret = get_next_line(0, &line);
	if (ret < 0)
		return (0);
	if (ret == 0)
		exit(0);
	if (*line == '\0')
		return (0);
	lst = create_list(line, env);
	free(line);
	 print_arg_list(lst);
	return (lst);
}

/*int exe_one_command(t_args *args_lst, char **envp[])
{
	int status; // код
	int fd_out;
	int fd_in;
	int fd;
	char buf[10];
	int n;

	status = 0;
	fd_out = dup(1);
	fd_in = dup(0);
	if(args_lst->file_option == NONE)
		status = execution(args_lst->args, envp);
	else if (args_lst->file_option == 2)
	{

		if ((fd = open(args_lst->file_path, O_RDONLY)) > 0)
		{
			dup2(fd, 0);
			if (args_lst->args[0][0])
				status = execution(args_lst->args, envp);
			else
				while ((n = read(0, buf, 10)) > 0)
					write(1, buf, n);
			close(fd);
			dup2(fd_in, 0);
		} else
			return (print_error_log("lsh: ", NULL, args_lst->file_path, "No such file or directory"));
	}
	else
	{
		if	(args_lst->file_option)
			fd = open(args_lst->file_path, O_RDWR | O_APPEND | O_CREAT, 00644);
		else
			fd = open(args_lst->file_path, O_RDWR | O_TRUNC | O_CREAT, 00644);
		dup2(fd, 1);
		status = execution(args_lst->args, envp);
		close(fd);
		dup2(fd_out, 1);
	}
	return(status);
}

int parse_str(t_args *args_lst, char **envp[])
{

	int fd_buf[2];
	pid_t child;
	int fd_in;
	int status;

	fd_in = dup(0);
	status = 0;
	while(args_lst)
	{
		pipe(fd_buf);
		if( args_lst->flag == COMMAND)
		{
			status = exe_one_command(args_lst, envp);
			args_lst = args_lst->next;
			dup2(fd_in, 0);
		}
		else if (args_lst->flag == PIPE)
		{

			if (!(child = fork())){
				dup2 (fd_buf[1], 1);
				close(fd_buf[0]);
				status = exe_one_command(args_lst, envp);
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
	return(status);
}*/

void    shell_loop(char *envp[])
{
	//int status;
    t_args *args_lst;

    while (1)
   	{
		//signal(SIGQUIT, sighandler);
		//signal(SIGINT, sighandler);

		flag = 0;
		write(1, "minishell : ", 12);
		//ft_putnbr_fd(last_code, 1);
		args_lst = get_argv(envp);
		free_args_list(&args_lst);
		//if (args_lst)
		//	status = parse_str(args_lst, &envp);
	//	last_code = status;
		//free_args_list(&args_lst);
		//write(1, "\n", 1);
		//if (!status)
		//	break ;
   }
}
