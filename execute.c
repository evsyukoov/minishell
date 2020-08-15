/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 18:50:16 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/13 20:07:57 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *pathfinder(char **envp)
{
	int i = 0;
	while(envp[i])
	{
		if ((ft_strncmp("PATH=", envp[i], 5)) == 0)
			return (envp[i]);
		i++;
	}
	return (0);
}

char *joinpath(char *path, char *exe)
{
	char	*res;
	int		len;
	int		i;

	if (!path || !exe)
		return (0);
	len = ft_strlen(path) + ft_strlen(exe);
	i = 0;
	res = (char*)malloc(sizeof(char) * (len + 2));
	if (!res)
		return (0);
	while (*path)
		res[i++] = *path++;
	res[i++] = '/';
	while (*exe)
		res[i++] = *exe++;
	res[i] = '\0';
	return (res);
}

int free_list(char **all_path)
{
	int i;

	i = 0;
	while(all_path[i])
		free(all_path[i++]);
	free(all_path);
	return(0);
}

int free_all(char **all_path, char *path)
{
	free(path);
	free_list(all_path);
	return(1);
}

int execute(char **argv, char *envp[])
{
	char *path;
	char **all_path;
	int i = 0;

	if((path = pathfinder(envp)))
	{
		if((all_path = ft_split(&path[4], ':')))
		{
			while(all_path[i])
			{
				if((path = joinpath(all_path[i] , argv[0])))
				{
					if (execve(path, &argv[0], envp) != -1)
						return (free_all(all_path, path));
					free(path);
				}
				i++;
			}
			free_list(all_path);
		}
	}
	return(-1);
}