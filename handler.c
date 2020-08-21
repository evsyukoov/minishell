/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 15:01:18 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/22 00:38:56 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	listener_ctrl_d(int signal_num)
{
	if (signal_num == SIGQUIT) {
		write(1, "\b\b  \n", 7);
		kill(lsh_child, SIGQUIT);
		// shell_loop(env_copy);
	}

}

void	sighandler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(1, "\b\b  \b\b\n", 7);
		write(1, "minishell : ", 12);
		
	}
	if (sig_num == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 7);
	}
}

void 	listener_ctrl_c(int signal_num)
{
	if (signal_num == SIGINT) {
			write(1, "\b\b  \n", 6);
			// kill(lsh_child, SIGINT);
			// shell_loop(env_copy);			
		}
}


