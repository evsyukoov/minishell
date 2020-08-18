/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 23:24:33 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/19 00:14:10 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		launch(char **argv, char *envp[])
{
	pid_t child;
	int  status;
	
	child = fork();
	if (child < 0)
	{
		perror("minishell");
	}
	else if (child == 0)
	{
		if (execute(argv, envp) == -1) {
			perror("command not found");
			return (1);
		}
	} 
	else
	{
		waitpid(child, &status, WUNTRACED);
		while (WIFEXITED(status) == 0)
			waitpid(child, &status, WUNTRACED);
	}
	return (1);
}

int     cd(char **argv)
{
	if (chdir(argv[1]) != 0)
    	perror(argv[1]);
    return (1);
}

void	free_arguments(char ***argv)
{
	int i;

	i = 0;
	if (*argv) {
		while ((*argv)[i])
			free((*argv)[i++]);
		free(*argv);
	}
}

int    execution(char **argv, char **envp[])
{
	char wd[256];

	if (ft_strcmp(argv[0], "cd") == 0)
		return (cd(argv));
	else if(ft_strcmp(argv[0], "pwd") == 0) {
		ft_putendl_fd(getwd(wd), 1);
		return (1);
	}
	else if (ft_strcmp(argv[0], "unset") == 0)
		return(unset(argv[1], *envp));
	else if (ft_strcmp(argv[0], "env") == 0)
		return(print_env(*envp));
	else if (ft_strcmp(argv[0], "export") == 0)
		return(export(argv[1], envp));
	else if (ft_strcmp(argv[0], "exit") == 0)
		exit(0);
	return (launch(argv, *envp));
}