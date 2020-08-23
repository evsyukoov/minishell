/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 23:24:33 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/22 19:50:19 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		is_contains_alpha(char *arg)
{
	while (*arg)
	{
		if (ft_isalpha(*arg))
			return (1);
		arg++;
	}
	return (0);
}

int		exit_program(char *arg)
{
	write(1, "exit\n", 5);
	if (arg)
	{
		if (is_contains_alpha(arg))
		{
			last_code = 255;
			exit(255);
		}
		else
		{
			last_code = ft_atoi(arg);
			if (last_code > 255)
				exit(0);
			else
				exit(last_code);
		}
	}
	else
		exit(0);
}

int		cd(char **argv)
{
	if (chdir(argv[1]) != 0)
	{
		print_error_log("lsh: ", "cd: ", argv[1], strerror(errno));
		return (1);
	}
	return (0);
}

void	free_arguments(char ***argv)
{
	int i;

	i = 0;
	if (*argv)
	{
		while ((*argv)[i])
			free((*argv)[i++]);
		free(*argv);
	}
}

int		execution(char **argv, char **envp[])
{
	char	wd[256];

	if (ft_strcmp(argv[0], "cd") == 0)
		return (cd(argv));
	else if (ft_strcmp(argv[0], "pwd") == 0)
	{
		ft_putendl_fd(getwd(wd), 1);
		return (0);
	}
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (unset(argv[1], *envp));
	else if (ft_strcmp(argv[0], "env") == 0)
		return (print_env(*envp, argv));
	else if (ft_strcmp(argv[0], "export") == 0)
		return (export(argv[1], envp));
	else if (ft_strcmp(argv[0], "exit") == 0)
		exit_program(argv[1]);
	return (launch(argv, *envp));
}
