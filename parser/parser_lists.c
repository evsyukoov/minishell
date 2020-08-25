/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 20:30:07 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/25 20:30:07 by ccarl            ###   ########.fr       */
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

int 	lst_size(t_str *str)
{
	int i;

	i = 0;
	while (str)
	{
		str = str->next;
		i++;
	}
	return (i);
}

int 	argv_size(t_node *node)
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

void 	add_to_str(t_str **head, char c)
{
	t_str *str;
	t_str *last;

	str = (t_str*)malloc(sizeof(t_str));
	str->curr = c;
	str->next = 0;
	if (!(*head))
	{
		*head = str;
		(*head)->next = NULL;
		return ;
	}
	last = get_last_char((*head));
	last->next = str;
	str->next = NULL;
}

void 	add_to_list(t_node **head, char *str)
{
	t_node *node;
	t_node *last;

	node = (t_node*)malloc(sizeof(t_node));
	node->str = str;
	node->next = 0;
	if (!(*head))
	{
		*head = node;
		(*head)->next = NULL;
		return ;
	}
	last = get_last((*head));
	last->next = node;
	node->next = NULL;
}

char 	**node_to_argv(t_node **head)
{
	int size;
	int i;
	char **res;
	t_node *tmp;

	size = argv_size(*head);
	i = 0;
	res = (char**)malloc(sizeof(char*) * (size + 1));
	while (i < size)
	{
		tmp = (*head);
		res[i++] = (*head)->str;
		(*head) = (*head)->next;
		free(tmp);
	}
	res[i] = NULL;
	return (res);
}

char 	*list_to_str(t_str **str)
{
	char	*res;
	int		i;
	t_str	*tmp;


	res = (char*)malloc(lst_size(*str) + 1);
	i = 0;
	while (*str)
	{
		tmp = *str;
		res[i++] = (*str)->curr;
		(*str) = (*str)->next;
		free(tmp);
	}
	res[i] = '\0';
	return (res);
}
