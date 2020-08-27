/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 17:47:50 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/27 17:51:30 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_double_quotes(t_str **head, char **s)
{
	(*s)++;
	while (**s)
	{
		if (**s == '\"' && *(*s - 1) != '\\' && (*s)++)
			break ;
		if (!is_spec_symbols(*s) || **s == '\'')
		{
			add_to_str(head, **s, NULL);
			(*s)++;
		}
		else
		{
			if (**s == '\\')
				*s = analize_slash(*s, head, 2);
			if (**s == '$')
				*s = parse_dollar(*s, head);
		}
	}
}

void	parse_simple_quotes(t_str **head, char **s)
{
	(*s)++;
	while (**s)
	{
		if (**s == '\'' && *(*s - 1) != '\\' && (*s)++)
			break ;
		add_to_str(head, **s, NULL);
		(*s)++;
	}
}
