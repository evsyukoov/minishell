/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 15:01:18 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/22 13:18:53 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	listener(int signal_num)
{
	if (signal_num == SIGQUIT) {
		write(1, "Quit  \n", 7);
		kill(lsh_child, SIGQUIT);
		last_code = 131;
	}
	if (signal_num == SIGINT) {
			write(1, "\b\b\n", 6);
			kill(lsh_child, SIGINT);
			last_code = 130;
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


