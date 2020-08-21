/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:49:32 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/21 23:22:07 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **realloc_env(char *envp[])
{
	char **new_env;
	char *buf;
	int i;

	new_env = malloc(sizeof(char *) * (env_len(envp)+ 1));
	i = 0;
	if(!new_env)
		return (NULL);		
	while(envp[i])
	{

		buf = malloc(ft_strlen(envp[i]) + 1);
		if(!buf)
			return (NULL);
		ft_strlcpy(buf, envp[i], 1 + ft_strlen(envp[i]));
		new_env[i] = buf;
		i++;
	}
	new_env[i] = 0;
	return(new_env);
}

int main(int argc, char *argv[], char *envp[])
{
	argc = 0;
	argv = 0;
	if(!(env_copy = realloc_env(envp)))
		return (0);
	shell_loop(env_copy);
	return (last_code);
}
