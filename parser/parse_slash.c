/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_slash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 17:49:17 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/27 17:57:55 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_slashes(t_str **head, int count, char c)
{
	int i;

	i = 0;
	while (i < count)
	{
		add_to_str(head, '\\', NULL);
		i++;
	}
	if (c)
		add_to_str(head, c, NULL);
}

int		count_slashes(char *s)
{
	int slashes;

	slashes = 0;
	while (s[slashes] == '\\')
		slashes++;
	return (slashes);
}

char	*ecranir_simple_quotes(char *s, t_str **head, int slashes, int flag)
{
	int fact;

	fact = slashes % 2 == 0 ? slashes / 2 : slashes / 2 + 1;
	if (flag == 2)
	{
		add_slashes(head, slashes == 1 ? slashes : fact, '\'');
		s += slashes + 1;
	}
	if (flag == 0)
	{
		add_slashes(head, slashes / 2, '\'');
		s += slashes + 1;
	}
	return (s);
}

char	*ecranir_dollar(char *s, t_str **head, int slashes)
{
	if (s[slashes + 1] == '?')
	{
		if (slashes % 2 == 0)
		{
			add_slashes(head, slashes / 2, 0);
			s += slashes;
		}
		else
		{
			add_slashes(head, slashes / 2, '$');
			s += slashes + 1;
		}
	}
	else if (slashes % 2 == 0)
	{
		add_slashes(head, slashes / 2, 0);
		s += slashes;
	}
	else
	{
		add_slashes(head, slashes / 2, '$');
		s += slashes + 1;
	}
	return (s);
}

char	*analize_slash(char *s, t_str **head, int flag)
{
	int slashes;

	slashes = count_slashes(s);
	if (s[slashes] == '\"')
	{
		add_slashes(head, slashes / 2, '\"');
		s += slashes + 1;
	}
	else if (s[slashes] == '$')
		s = ecranir_dollar(s, head, slashes);
	else if (s[slashes] == '\'')
		s = ecranir_simple_quotes(s, head, slashes, flag);
	return (s);
}
