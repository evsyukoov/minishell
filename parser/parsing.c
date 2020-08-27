/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:40:29 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/27 18:00:43 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*parsing(char *s, t_str **str)
{
	if (*s == '~')
		s = parse_home_path(s, str);
	if (*s == '\"' && *(s - 1) != '\\')
		parse_double_quotes(str, &s);
	if (*s == '\'' && *(s - 1) != '\\')
		parse_simple_quotes(str, &s);
	if (*s == '\\')
		s = analize_slash(s, str, 0);
	if (*s == '$')
		s = parse_dollar(s, str);
	if (!is_spec_symbols(s) && *s && *s != ' ' && !is_redirections(s))
	{
		add_to_str(str, *s, NULL);
		s++;
	}
	return (s);
}

char	**split_arg(char *s, t_files **files)
{
	t_node	*node;
	t_str	*str;
	int		flag;

	node = NULL;
	skip(&s, ' ');
	while (*s)
	{
		str = NULL;
		while (*s && *s != ' ')
		{
			flag = redirection_parser_loop(&s, files, str, &node);
			if (flag == -1)
				return (0);
			if (flag)
				return (node_to_argv(&node));
			s = parsing(s, &str);
		}
		add_to_list(&node, list_to_str(&str));
		skip(&s, ' ');
	}
	return (node_to_argv(&node));
}
