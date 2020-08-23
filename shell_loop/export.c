/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 18:02:47 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/22 19:46:21 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_name(char *arg)
{
	int	i;

	i = 0;
	if (!(ft_isdigit(arg[0])) && arg[0] != ' ')
	{
		while (arg[i] != '=')
		{
			if (arg[i] == ' ' || !arg[i])
				return (NULL);
			i++;
		}
		return (ft_substr(arg, 0, i));
	}
	return (NULL);
}

char	*get_value(char *arg)
{
	if (!arg[0] || arg[0] == ' ')
		return (NULL);
	if (arg[0] == '\'')
		return (ft_strtrim(arg, "\'"));
	if (arg[0] == '\"')
		return (ft_strtrim(arg, "\""));
	return (ft_strdup(arg));
}

char	**insert_var(char *name, char *value, char *envp[])
{
	int		len;
	char	**new_env;
	int		i;

	i = 0;
	len = env_len(envp);
	if (!(new_env = malloc(sizeof(char *) * (len + 2))))
		return (NULL);
	new_env[len + 2] = 0;
	while (i < len)
	{
		if (i == len - 1)
		{
			new_env[i + 1] = envp[i];
			if (!(new_env[i] = joinenv(name, value)))
				return (NULL);
			break ;
		}
		new_env[i] = envp[i];
		i++;
	}
	new_env[i + 2] = 0;
	return (new_env);
}

int		rewrite_var(char *name, char *value, char *envp[])
{
	int		i;
	char	*buf;

	i = 0;
	while (envp[i])
	{
		if (!(env_strcmp(name, envp[i])))
		{
			buf = joinenv(name, value);
			if (!buf)
				return (0);
			envp[i] = buf;
			return (1);
		}
		i++;
	}
	return (0);
}

int		export(char *arg, char **envp[])
{
	char	*name;
	char	*value;
	char	**buf;

	if (!arg)
	{
		print_env(*envp, NULL);
		return (0);
	}
	if ((name = get_name(arg)))
	{
		if ((value = get_value(&arg[ft_strlen(name) + 1])))
		{
			if (rewrite_var(name, value, *envp))
				return (0);
			if ((buf = insert_var(name, value, *envp)))
			{
				*envp = buf;
				return (0);
			}
		}
	}
	return (1);
}
