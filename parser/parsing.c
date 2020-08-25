/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:40:29 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/25 20:36:45 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int 	count_slashes(char *s)
{
	int len;

	len = 0;
	while (s[len] == '\\')
		len++;
	len /= 2;
	return (len);
}

void 	parse_double_quotes(t_str **head, char **s)
{
	(*s)++;
	while (**s && **s != '\"')
	{
		add_to_str(head, **s);
		(*s)++;
	}
}

void 	parse_simple_quotes(t_str **head, char **s)
{
	(*s)++;
	while (**s && **s != '\'')
	{
		add_to_str(head, **s);
		(*s)++;
	}
}

char 	**split_arg(char *s, char **env)
{
	t_node	*node;
	t_str	*str;
	char 	*string;

	node = NULL;
	skip(&s, ' ');
	while (*s)
	{
		str = NULL;
		while (*s && *s != ' ')
		{
			if (*s == '\"' && *(s - 1) != '\\')
				parse_double_quotes(&str, &s);
			else if (*s == '\'' && *(s - 1) != '\\')
				parse_simple_quotes(&str, &s);
			else if (*s == '\\')
				s += count_slashes(s);
			else
				add_to_str(&str, *s);
			s++;
		}
		string =  list_to_str(&str);
		add_to_list(&node, string);
		skip(&s, ' ');
	}
	return (node_to_argv(&node));
}
