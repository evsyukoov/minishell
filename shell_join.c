/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:08:04 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/14 16:38:29 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shell_strdup(const char *str, char del)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] == del)
		i++;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (0);
	while (str[i])
	{
		if (str[i] == del)
			break ;
		res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

char	*shell_join(char const *s1, char const *s2, char del)
{
	char	*res;
	int		len;
	int		i;

	if (!s2)
		return (0);
	if (!s1)
		return (shell_strdup(s2, del));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	i = 0;
	res = (char*)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	while (*s1)
		res[i++] = *s1++;
	res[i++] = ' ';
	while (*s2)
	{
		if (*s2 == del)
			break;
		res[i++] = *s2++;
	}
	res[i] = '\0';
	return (res);
}

