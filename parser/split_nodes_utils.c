/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_nodes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:04:46 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/27 18:09:16 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		number_of_arguments(char **argv)
{
	int j;

	j = 0;
	while (argv[j])
		j++;
	return (j);
}

int		is_pipe(char *s)
{
	char q_type;

	while (s && *s)
	{
		q_type = quote_type(s);
		while (q_type)
		{
			skip_quotes(&s, q_type);
			q_type = quote_type(s);
		}
		if (*s == '|')
			return (1);
		if (*s != 0)
			s++;
	}
	return (0);
}

int		is_pipe_end(char *arg)
{
	int end;

	end = (int)ft_strlen(arg) - 1;
	while (arg[end] == ' ' && arg[end] != *arg)
		end--;
	if (arg[end] == '|')
		return (1);
	return (0);
}

void	change_option(t_args *lst)
{
	while (lst->next)
		lst = lst->next;
	lst->flag = PIPE;
}
