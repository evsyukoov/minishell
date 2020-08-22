/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:49:32 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/21 17:39:19 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **realloc_env(char *envp[])
{
	char **new_env;
	char *buf;
	int i;

	new_env = malloc(sizeof(char *) * (env_len(envp) + 1));
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

void 	free_args_list(t_args **lst)
{
	t_args *tmp;
	t_args *head;

	head = *lst;
	while (head)
	{
		int i;

		i = 0;
		tmp = head;
		while ((head->args)[i])
			free(head->args[i++]);
		free(head->args);
		free(head->file_path);
		head = head->next;
		free(tmp);
	}
}

int main(int argc, char *argv[], char *envp[])
{
	int status;

	argc = 0;
	argv = 0;
	if(!(env_copy = realloc_env(envp)))
		return (0);
	if ((shell_pid = fork()) == 0) {
		shell_loop(env_copy);
	}
	else
		{
		//signal(SIGQUIT, &nothing);
		signal(SIGINT, &listener_ctrl_c);
		while (wait(&status) > 0)
			continue ;

	}
	free_arguments(&env_copy);
	return (last_code);
}
