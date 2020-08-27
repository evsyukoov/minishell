/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:29:37 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/25 23:43:57 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int echo (char *argv[])
{
	int nflag;
	
	if (*argv && !ft_strcmp(*argv, "-n")) {
		++argv;
		nflag = 1;
	}
	else
		nflag = 0;
	while (*argv)
	{
		ft_putstr_fd(*argv, 1);
		if (*++argv)
			ft_putchar_fd(' ', 1);
	}
	if (!nflag)
		ft_putchar_fd('\n', 1);
	return (0);
}