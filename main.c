/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:49:32 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/27 19:06:01 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	**realloc_env(char *envp[])
{
	int		i;

	g_env_copy = malloc(sizeof(char *) * (env_len(envp) + 1));
	i = 0;
	if (!g_env_copy)
		return (NULL);
	while (envp[i])
	{
		if (!(g_env_copy[i] = ft_strdup(envp[i])))
			return (0);
		i++;
	}
	g_env_copy[i] = 0;
	return (g_env_copy);
}

int		main(int argc, char *argv[], char *envp[])
{
	argc = 0;
	argv = 0;
	if (!(g_env_copy = realloc_env(envp)))
		return (0);
	shell_loop();
	free_arguments(&g_env_copy);
	return (g_last_code);
}
