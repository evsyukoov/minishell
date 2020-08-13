/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:04:08 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/13 19:28:52 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//функции-помощники для отладки

#include "minishell.h"

void 	print_arg_list(t_args *lst)
{
	int i;
	int j;

	j = 0;
	while (lst)
	{
		i = 0;
		printf("Node number = %d Node info = %s\n", j, lst->flag == 0 ? "Command" : "Pipe");
   		while ((lst->args)[i])
   			printf("%s\n", (lst->args)[i++]);
   		lst = lst->next;
   		j++;
	}
}
