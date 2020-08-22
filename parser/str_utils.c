/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:31:10 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/22 21:20:02 by mcaptain         ###   ########.fr       */
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

int		str_startswith(char *s, char *set)
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
