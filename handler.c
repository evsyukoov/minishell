/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 15:01:18 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/19 20:20:03 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	listener_ctrl_d(int signal_num)
{
	if (child == 0 && signal_num == SIGQUIT)
		kill(child, SIGKILL);
}

void 	listener_ctrl_c(int signal_num)
{
	if (signal_num == SIGINT) {
		if (kill(shell_pid, SIGTERM) < 0)
			exit(-1);
		if (!(shell_pid = fork())) {
			write(1, "\b\b  \n", 5);
			shell_loop(env_copy);
		}
	}
}


