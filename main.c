/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:49:32 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/23 19:55:30 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**realloc_env(char *envp[])
{
	char	**new_env;
	char	*buf;
	int		i;

	new_env = malloc(sizeof(char *) * (env_len(envp) + 1));
	i = 0;
	if (!new_env)
		return (NULL);
	while (envp[i])
	{
		buf = malloc(ft_strlen(envp[i]) + 1);
		if (!buf)
			return (NULL);
		ft_strlcpy(buf, envp[i], 1 + ft_strlen(envp[i]));
		new_env[i] = buf;
		i++;
	}
	new_env[i] = 0;
	return (new_env);
}

void	free_args_list(t_args **lst)
{
	t_args	*tmp;
	t_args	*head;
	t_files	*tmp2;
	int		i;

	head = *lst;
	while (head)
	{
		i = 0;
		tmp = head;
		while ((head->args)[i])
			free(head->args[i++]);
		free(head->args);
		while (head->files)
		{
			tmp2 = head->files;
			free(head->files->name);
			head->files = head->files->next;
			free(tmp2);
		}
		head = head->next;
		free(tmp);
	}
}

int		main(int argc, char *argv[], char *envp[])
{
	argc = 0;
	argv = 0;
	if (!(g_env_copy = realloc_env(envp)))
		return (0);
	shell_loop(g_env_copy);
	return (g_last_code);
}
