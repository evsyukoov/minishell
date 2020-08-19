/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:49:32 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/19 20:25:08 by ccarl            ###   ########.fr       */
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
	int status;

	argc = 0;
	argv = 0;
	if(!(env_copy = realloc_env(envp)))
		return (0);
	if ((shell_pid = fork()) == 0)
		shell_loop(env_copy);
	else
		{
		signal(SIGINT, &listener_ctrl_c);
		signal(SIGQUIT, &listener_ctrl_d);
		while (wait(&status) > 0)
			NULL;
	}
	return 0;
}
