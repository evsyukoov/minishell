/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:04:08 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/22 20:41:20 by ccarl            ###   ########.fr       */
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
		printf("Node number = %d, Node info = %s\n",
				j, lst->flag == 0 ? "Command" : "Pipe");
		int i = 0;
		printf("Files :   \n");
		while (lst->files)
		{
			printf("file #%d = %s option = %d\n", i, lst->files->name, lst->files->type);
			lst->files = lst->files->next;
			i++;
		}
		printf("Argv :    \n");
   		print_argv(lst->args);
   		lst = lst->next;
   		j++;
	}
}

