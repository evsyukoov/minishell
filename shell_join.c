/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:08:04 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/13 20:08:04 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shell_join(char const *s1, char const *s2)
{
	char	*res;
	int		len;
	int		i;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	i = 0;
	res = (char*)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	while (*s1)
		res[i++] = *s1++;
	res[i++] = ' ';
	while (*s2)
		res[i++] = *s2++;
	res[i] = '\0';
	return (res);
}

