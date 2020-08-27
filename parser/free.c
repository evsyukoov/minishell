/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 17:43:40 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/27 17:50:56 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_files(t_files **files)
{
	t_files *tmp;

	while (*files)
	{
		tmp = *files;
		free((*files)->name);
		*files = (*files)->next;
		free(tmp);
	}
}

void	free_nodes(t_node **head)
{
	t_node *tmp;

	while (*head)
	{
		tmp = *head;
		free((*head)->str);
		*head = (*head)->next;
		free(tmp);
	}
}

void	free_args_list(t_args **lst)
{
	t_args	*tmp;
	t_args	*head;
	t_files	*tmp2;
	int		i;

	head = *lst;
	while (head)
	{
		i = 0;
		tmp = head;
		while ((head->args)[i])
			free(head->args[i++]);
		free(head->args);
		while (head->files)
		{
			tmp2 = head->files;
			free(head->files->name);
			head->files = head->files->next;
			free(tmp2);
		}
		head = head->next;
		free(tmp);
	}
}
