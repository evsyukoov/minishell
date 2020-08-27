/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 17:39:30 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/27 18:02:36 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		is_redirections(char *s)
{
	if (*s == '>' || *s == '<')
		return (1);
	return (0);
}

int		check_for_newline_error(char *s)
{
	while (*s && *s == ' ')
		s++;
	if (!*s)
		return (0);
	return (1);
}

char	*count_redirections(char *s, int *count, char type)
{
	while (*s == type)
	{
		s++;
		(*count)++;
	}
	return (s);
}

int		type_of_redirection(char **s)
{
	int count;

	count = 0;
	*s = count_redirections(*s, &count, '>');
	if (!check_for_newline_error(*s))
		return ((int)parse_syntax_error(2));
	if (count > 2)
		return ((int)parse_syntax_error(3));
	if (count == 2)
		return (WRITE);
	if (count == 1)
		return (REWRITE);
	count = 0;
	*s = count_redirections(*s, &count, '<');
	if (!check_for_newline_error(*s))
		return ((int)parse_syntax_error(2));
	if (count > 1)
		return ((int)parse_syntax_error(4));
	if (count == 1)
		return (REVERSE);
	return (0);
}

char	*wait_for_next_redirect(char *s)
{
	skip(&s, ' ');
	while (*s && !is_redirections(s))
		s++;
	return (s);
}
