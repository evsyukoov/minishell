/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:01:17 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/23 19:55:20 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_args	*create_new_node(char **s, int g_flag, t_files *files)
{
	t_args *node;

	node = (t_args*)malloc(sizeof(t_args));
	node->args = s;
	node->flag = g_flag;
	node->files = files;
	return (node);
}

t_args	*lstlast(t_args *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	push(t_args **lst, t_args *new)
{
	t_args *last;

	if (!(*lst))
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	last = lstlast((*lst));
	last->next = new;
	new->next = NULL;
}
