/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:20:27 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/27 22:28:48 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		print_error_log(char *lsh, char *command, char *argument, char *msg)
{
	if (lsh)
		write(2, lsh, ft_strlen(lsh));
	if (command)
		write(2, command, ft_strlen(command));
	if (argument)
	{
		write(2, argument, ft_strlen(argument));
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
}

t_args	*get_argv()
{
	char	*line;
	t_args	*lst;
	int		ret;

	line = NULL;
	lst = NULL;
	ret = get_next_line(0, &line);
	if (ret < 0)
		return (0);
	if (ret == 0)
		exit(0);
	if (*line == '\0')
		return (0);
	lst = create_list(line);
	free(line);
	return (lst);
}

int		fork_dup(t_args *args_lst, char **envp[])
{
	pid_t	child;
	int		fd_buf[2];
	int		status;

	pipe(fd_buf);
	if (!(child = fork()))
	{
		dup2(fd_buf[1], 1);
		close(fd_buf[0]);
		status = exe_one_command(args_lst, envp);
		exit(0);
	}
	else
	{
		waitpid(child, &status, WUNTRACED);
		dup2(fd_buf[0], 0);
		close(fd_buf[1]);
	}
	return (status);
}

int		parse_str(t_args *args_lst, char **envp[])
{
	int	fd_in;
	int	status;

	fd_in = dup(0);
	status = 0;
	while (args_lst)
	{
		if (args_lst->flag == COMMAND)
		{
			status = exe_one_command(args_lst, envp);
			dup2(fd_in, 0);
		}
		else if (args_lst->flag == PIPE)
			status = fork_dup(args_lst, envp);
		args_lst = args_lst->next;
	}
	return (status);
}

void	shell_loop()
{
	int		status;
	t_args	*args_lst;

	args_lst = NULL;
	while (1)
	{
		signal(SIGQUIT, sighandler);
		signal(SIGINT, sighandler);
		write(1, "minishell : ", 12);
		args_lst = get_argv();
		if (args_lst)
		{
			status = parse_str(args_lst, &g_env_copy);
			g_last_code = status;
		}
		free_args_list(&args_lst);
	}
}
