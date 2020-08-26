/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 19:47:25 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/26 20:30:46 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	return_launch(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			return (130);
		else if (WTERMSIG(status) == 3)
			return (131);
	}
	return (WEXITSTATUS(status));
}

int	launch(char **argv)
{
	int	status;

	status = 0;
	g_lsh_child = fork();
	if (g_lsh_child < 0)
		perror("minishell");
	else if (g_lsh_child == 0)
	{
		if (execute(argv) == -1)
		{
			print_error_log("lsh: ", NULL, argv[0], "command not found");
			exit(127);
		}
	}
	else
	{
		signal(SIGQUIT, listener);
		signal(SIGINT, listener);
		waitpid(g_lsh_child, &status, WUNTRACED);
	}
	return (return_launch(status));
}
