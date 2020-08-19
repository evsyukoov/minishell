/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:04:08 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/15 19:21:16 by ccarl            ###   ########.fr       */
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
		printf("Node number = %d, Node info = %s, File path : %s, File option : %s\n", j, lst->flag == 0 ? "Command" : "Pipe", lst->file_path, lst->file_option == 2 ? "> (REVERSE)" : ">> (WRITE)");
   		print_argv(lst->args);
   		lst = lst->next;
   		j++;
	}
}

