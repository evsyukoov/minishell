/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:04:08 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/15 15:41:44 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//функции-помощники для отладки

#include "minishell.h"

void 	print_argv(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		printf("%s\n", argv[i++]);
}

void 	print_arg_list(t_args *lst)
{
	int j;

	j = 0;
	while (lst)
	{
		printf("Node number = %d Node info = %s\n", j, lst->flag == 0 ? "Command" : "Pipe");
   		print_argv(lst->args);
   		lst = lst->next;
   		j++;
	}
}

