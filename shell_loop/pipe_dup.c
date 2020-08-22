/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 19:52:29 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/22 20:40:07 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_from(t_args *args_lst, char **envp[])
{
	int	fd;

	if ((fd = open(args_lst->file_path, O_RDONLY)) > 0)
	{
		dup2(fd, 0);
		if (args_lst->args[0])
			return (execution(args_lst->args, envp));
		return (0);
	}
	else
		return (print_error_log("lsh: ", NULL,
		args_lst->file_path, "No such file or directory"));
}

int	write_to(t_args *args_lst, char **envp[])
{
	int	fd;

	if (args_lst->file_option)
		fd = open(args_lst->file_path, O_RDWR | O_APPEND | O_CREAT, 00644);
	else
		fd = open(args_lst->file_path, O_RDWR | O_TRUNC | O_CREAT, 00644);
	dup2(fd, 1);
	if (args_lst->args[0])
		return (execution(args_lst->args, envp));
	return (0);
}

int	redirection(t_args *args_lst, char **envp[])
{
	if (args_lst->file_option == 2)
		return (read_from(args_lst, envp));
	else
		return (write_to(args_lst, envp));
	return (0);
}

int	exe_one_command(t_args *args_lst, char **envp[])
{
	int	status;
	int	fd_out;
	int	fd_in;

	status = 0;
	fd_out = dup(1);
	fd_in = dup(0);
	if (args_lst->file_option == NONE)
		status = execution(args_lst->args, envp);
	else
		status = redirection(args_lst, envp);
	dup2(fd_out, 1);
	dup2(fd_in, 0);
	return (status);
}
