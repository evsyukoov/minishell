/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 22:48:58 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/25 21:07:36 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		env_len2(char *arg)
{
	int i;

	i = 0;
	while (arg[i] && arg[i] != ' ' && arg[i] != '\'' && arg[i] != '\"'
	&& arg[i] != '\\' && arg[i] != '$' && arg[i] != '=')
		i++;
	return (i);
}

char	*init_env_name(char *arg)
{
	char	*name;
	int		i;
	int len;

	arg += 1;
	len = env_len2(arg);
	name = (char*)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
		name[i++] = *arg++;
	name[i] = '\0';
	return (name);
}
