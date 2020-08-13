/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:01:17 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/13 16:46:37 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args 		*create_new_node(char **s, int flag)
{
	t_args *node;

	node = (t_args*)malloc(sizeof(t_args));
	node->args = s;
	node->flag = flag;
	node->next = NULL;
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

