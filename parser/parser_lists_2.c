/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lists_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <ccarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 17:28:28 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/27 17:36:46 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_to_str(t_str **head, char c, char *string)
{
	t_str *str;
	t_str *last;

	str = (t_str*)malloc(sizeof(t_str));
	if (c)
	{
		str->curr = c;
		str->string = NULL;
	}
	else if (string)
		str->string = string;
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

void	add_to_list(t_node **head, char *str)
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

char	**node_to_argv(t_node **head)
{
	int		size;
	int		i;
	char	**res;
	t_node	*tmp;

	size = argv_size(*head);
	i = 0;
	res = (char**)malloc(sizeof(char*) * (size + 1));
	while (*head)
	{
		tmp = (*head);
		res[i++] = (*head)->str;
		(*head) = (*head)->next;
		free(tmp);
	}
	res[i] = NULL;
	return (res);
}

char	*list_to_str(t_str **str)
{
	char	*res;
	int		i;
	t_str	*tmp;
	char	*st_tmp;

	res = (char*)malloc(lst_size(*str) + 1);
	i = 0;
	while (*str)
	{
		tmp = *str;
		if ((*str)->string)
		{
			st_tmp = (*str)->string;
			while (*(*str)->string)
				res[i++] = *(*str)->string++;
			free(st_tmp);
		}
		else
			res[i++] = (*str)->curr;
		(*str) = (*str)->next;
		free(tmp);
	}
	res[i] = '\0';
	return (res);
}
