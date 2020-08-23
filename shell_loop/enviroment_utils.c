/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 17:50:35 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/22 14:10:35 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		print_env(char *envp[], char **argv)
{
	int	i;

	i = 0;
	if (argv && argv[1])
	{
		//print_error_log(NULL, "env: ", argv[1], "No such file or directory");
		return (127);
	}
	while (envp[i])
	{
		write(1, envp[i], ft_strlen(envp[i]));
		i++;
		write(1, "\n", 1);
	}
	return (0);
}

char	*joinenv(char *name, char *value)
{
	char	*res;
	int		i;
	int		j;

	j = 0;
	i = 0;
	res = (char*)malloc((ft_strlen(name) + ft_strlen(value) + 2));
	if (!res)
		return (0);
	while (name[j])
		res[i++] = name[j++];
	j = 0;
	res[i++] = '=';
	while (value[j])
		res[i++] = value[j++];
	free(value);
	free(name);
	res[i] = '\0';
	return (res);
}

int		env_strcmp(char *name, char *env_var)
{
	int	i;

	i = 0;
	while (name[i] == env_var[i])
		i++;
	if (name[i] == 0 && env_var[i] == '=')
		return (0);
	return (1);
}

int		env_len(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	*get_env_var(char *name, char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!(env_strcmp(name, envp[i])))
			return (&envp[i][ft_strlen(name) + 1]);
		i++;
	}
	return (NULL);
}
