/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:04:08 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/26 02:05:16 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		free_list(char **all_path)
{
	int i;

	i = 0;
	while (all_path[i])
		free(all_path[i++]);
	free(all_path);
	return (0);
}

int		free_all(char **all_path, char *path)
{
	free(path);
	free_list(all_path);
	return (1);
}


int isEnvValid(char c)
{
	return(ft_isdigit(c) || ft_isalpha(c) || c== '_');
}

int envLen(char *str)
{
	int i;

	i = 0;
	if(str[i++] != '$')
		return (0);
	if (!str[i])
		return (i);
	if (ft_isdigit(str[i++]))
		return (i);		
	while(isEnvValid(str[i]))
		i++;
	return (i);
}

char *envRet(char *str, char *envp[])
{
	int len;
	char *name;
	char *res;
	
	if ((len = envLen(str)) > 1)
	{
		if ((name = ft_substr(str, 1, len - 1)))
		{
			res = get_env_var(name, envp);
			free(name);
		}
		if (res)
			return(ft_strdup(res));
		return (NULL);
	}
	return (ft_strdup("$"));
}
