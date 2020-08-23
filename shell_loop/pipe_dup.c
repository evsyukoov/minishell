/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 19:52:29 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/23 16:44:03 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_from(t_files *file)
{
	int	fd;

	if ((fd = open(file->name, O_RDONLY)) > 0)
		dup2(fd, 0);
	return (fd);
}

int	write_to(t_files *file)
{
	int	fd;

	if (file->type)
		fd = open(file->name, O_RDWR | O_APPEND | O_CREAT, 00644);
	else
		fd = open(file->name, O_RDWR | O_TRUNC | O_CREAT, 00644);
	if (fd > 0)	
		dup2(fd, 1);
	return (fd);
}

int	redirection(t_args *args_lst, char **envp[])
{
	int fd_read;
	int fd_write;
	t_files *tmp;

	tmp = args_lst->files;
	fd_read = 0;
	fd_write = 0;
	while(tmp)
	{
		if (tmp->type == 2)
			fd_read  = (read_from(tmp));
		else
			fd_write = (write_to(tmp));
		tmp = tmp->next;
	}
	return (execution(args_lst->args, envp));
}

int	exe_one_command(t_args *args_lst, char **envp[])
{
	int	status;
	int	fd_out;
	int	fd_in;

	status = 0;
	fd_out = dup(1);
	fd_in = dup(0);
	if (args_lst->files)
		status = redirection(args_lst, envp);
	else
		status = execution(args_lst->args, envp);
	dup2(fd_out, 1);
	dup2(fd_in, 0);
	return (status);
}
