/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 19:47:25 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/23 19:54:37 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	launch(char **argv, char *envp[])
{
	int	status;

	status = 0;
	g_lsh_child = fork();
	if (g_lsh_child < 0)
		perror("minishell");
	else if (g_lsh_child == 0)
	{
		if (execute(argv, envp) == -1)
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
