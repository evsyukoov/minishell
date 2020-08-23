/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 17:42:19 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/23 16:45:23 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_files	*new_redirection(char *file_path, int file_option)
{
	t_files *node;

	node = (t_files*)malloc(sizeof(t_files));
	node->name = file_path;
	if (file_path)
		node->name = ft_strdup(file_path);
	else
		node->name = NULL;
	node->type = file_option;
	node->next = NULL;
	return (node);
}

t_files	*lstlast_redirect(t_files *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	push_redirect(t_files **lst, t_files *new)
{
	t_files *last;

	if (!(*lst))
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	last = lstlast_redirect((*lst));
	last->next = new;
	new->next = NULL;
}

void 	free_redirections(t_files **lst)
{
	t_files *head;
	t_files *tmp;

	head = *lst;
	while (head)
	{
		tmp = head;
		free(head->name);
		head = head->next;
		free(tmp);
	}
}



