/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:31:10 by ccarl             #+#    #+#             */
/*   Updated: 2020/07/23 19:33:18 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		str_endswith(char *s, char *set)
{
	char *s_end;
	char *set_end;

	s_end = s + ft_strlen(s);
	set_end = set + ft_strlen(set);
	while (s_end != s && *s_end == *set_end && set_end != set)
	{
		s_end--;
		set_end--;
	}
	if (set_end == set && *set == *s_end)
		return (1);
	return (0);
}

int		ft_str_startswith(char *s, char *set)
{
	while (*s && *set)
	{
		if (*s != *set)
			return (0);
		s++;
		set++;
	}
	return (1);
}