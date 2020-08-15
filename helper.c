/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:04:08 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/13 19:28:52 by ccarl            ###   ########.fr       */
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
<<<<<<< HEAD
	int j;

	j = 0;
	while (lst)
	{
		printf("Node number = %d Node info = %s\n", j, lst->flag == 0 ? "Command" : "Pipe");
   		print_argv(lst->args);
   		lst = lst->next;
   		j++;
=======
//	printf("_________________________________ARGS LIST________________________________________\n");
	while (lst)
	{
		// printf("%s\n", lst->args);
		lst = lst->next;
>>>>>>> 709f16b35aacc37326db6beef68d3f5e9636c42d
	}
}

