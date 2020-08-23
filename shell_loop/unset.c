/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 17:54:23 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/22 21:03:11 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		delete_env(int position, char *envp[])
{
	free(envp[position]);
	envp[position] = envp[position + 1];
	position++;
	while (envp[position])
	{
		envp[position] = envp[position + 1];
		position++;
	}
	return (0);
}

int		unset(char *name, char *envp[])
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!(env_strcmp(name, envp[i])))
			return (delete_env(i, envp));
		i++;
	}
	return (0);
}
