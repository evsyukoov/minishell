/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <ccarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 20:30:07 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/27 17:31:41 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_str	*get_last_char(t_str *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_node	*get_last(t_node *node)
{
	while (node->next)
		node = node->next;
	return (node);
}

int		lst_size(t_str *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str)
	{
		tmp = str->string;
		while (tmp && *tmp)
		{
			tmp++;
			i++;
		}
		str = str->next;
		i++;
	}
	return (i);
}

int		argv_size(t_node *node)
{
	int i;

	i = 0;
	while (node)
	{
		node = node->next;
		i++;
	}
	return (i);
}
