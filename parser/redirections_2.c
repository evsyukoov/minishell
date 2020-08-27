/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 17:41:59 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/27 18:03:40 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*parse_redirect(char *s, t_files **files)
{
	t_str *str;
	int flag;

	str = NULL;
	flag = type_of_redirection(&s);
	if (!flag)
	{
		free_files(files);
		*files = NULL;
		return (0);
	}
	skip(&s, ' ');
	while (*s && *s != ' ' && *s != '>' && *s != '<')
		s = parsing(s, &str);
	push_redirect(files, new_redirection(list_to_str(&str), flag));
	return (s);
}

int		redirection_parser_loop(char **s, t_files **files, t_str *str, t_node **node)
{
	int flag;

	flag = 0;
	if (is_redirections(*s) && ++flag)
	{
		if (str)
			add_to_list(node, list_to_str(&str));
		while (**s)
		{
			if (!(*s = parse_redirect(*s, files)))
			{
				free_nodes(node);
				return (-1);
			}
			*s = wait_for_next_redirect(*s);
		}
	}
	return (flag);
}

