/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 15:52:05 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/16 18:24:25 by mcaptain         ###   ########.fr       */
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

		buf = malloc(ft_strlen(envp[i] + 1));
		if(!buf)
			return (NULL);
		ft_strlcpy(buf, envp[i], 1 + ft_strlen(envp[i]));
		new_env[i] = buf;
		i++;
	}
	new_env[i] = 0;
	return(new_env);
}

//перемалочиваем список переменных увеличивая на один и вставляя переменную предпоследней

int main(int argc, char *argv[], char *envp[])
{
	char **new_envp;
	
	argc = 0;
	argv = 0;
	if(!(new_envp = realloc_env(envp)))
		return(0);
	// export("", &new_envp);
	// unset("COLORTERM", new_envp);
	// export("SECURITYSESSIONID=#ffff00", &new_envp);
	// print_env(new_envp);
 
    return 0;
}