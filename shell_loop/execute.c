/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 18:50:16 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/26 23:21:00 by mcaptain         ###   ########.fr       */
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
	if ((all_path = ft_split(&path[5], ':')))
	{
		while (all_path[i])
		{
			if ((path = joinpath(all_path[i], argv[0])))
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

int		execute(char **argv)
{
	char	*path;
	char	*join_path;
	int n;
	
	path = NULL;
	if (argv[0][0] == '/')
		return (execve(argv[0], &argv[0], g_env_copy));
	if (argv[0][0] == '.' && argv[0][1] == '/')
	{
		path = getcwd(path, 0);
		join_path = joinpath(path, argv[0]);
		n = execve(join_path, &argv[0], g_env_copy);
		free(path);
		free(join_path);
		return (n);
	}
	if ((path = pathfinder(g_env_copy)))
		return (norminette_path(argv, g_env_copy, path));
	return (-1);
}
