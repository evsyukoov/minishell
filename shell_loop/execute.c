/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 18:50:16 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/22 19:36:22 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*pathfinder(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if ((ft_strncmp("PATH=", envp[i], 5)) == 0)
			return (envp[i]);
		i++;
	}
	return (0);
}

char	*joinpath(char *path, char *exe)
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

int		norminette_path(char **argv, char *envp[], char *path)
{
	int		i;
	char	**all_path;

	i = 0;
	if ((all_path = ft_split(&path[4], ':')))
	{
		while (all_path[i])
		{
			if (argv[0][0] == '/')
			{
				if (execve(argv[0], &argv[0], envp) != -1)
					return (free_all(all_path, path));
			}
			else if ((path = joinpath(all_path[i], argv[0])))
			{
				if (execve(path, &argv[0], envp) != -1)
					return (free_all(all_path, path));
				free(path);
			}
			i++;
		}
		free_list(all_path);
	}
	return (-1);
}

int		execute(char **argv, char *envp[])
{
	char	*path;

	if ((path = pathfinder(envp)))
		return (norminette_path(argv, envp, path));
	return (-1);
}
