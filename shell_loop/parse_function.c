/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 23:24:33 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/27 21:09:15 by ccarl            ###   ########.fr       */
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
	if (arg + 1)
	{
		print_error_log("lsh: ", "exit: ", NULL, "too many arguments");
		return (1);
	}
	if (arg)
	{
		if (is_contains_alpha(arg))
		{
			g_last_code = 255;
			print_error_log("lsh: ", "exit: ", arg, "numeric argument required");
			exit(255);
		}
		else
		{
			g_last_code = ft_atoi(arg);
			if (g_last_code > 255)
				exit(0);
			else
				exit(g_last_code);
		}
	}
	else
		exit(0);
}

int		cd(char **argv, char *envp[])
{
	char	*path;
	int		g_flag;

	g_flag = 0;
	path = argv[1];
	if (!argv[1])
	{
		g_flag = 1;
		path = get_env_var("HOME", envp);
	}
	if (chdir(path) != 0)
	{
		print_error_log("lsh: ", "cd: ", argv[1], strerror(errno));
		return (1);
	}
	return (0);
}

void	*free_arguments(char ***argv)
{
	int i;

	i = 0;
	if (*argv)
	{
		while ((*argv)[i])
			free((*argv)[i++]);
		free(*argv);
	}
	return (0);
}

int		execution(char **argv, char **envp[])
{
	char	*wd;

	wd = NULL;
	if (ft_strcmp(argv[0], "cd") == 0)
		return (cd(argv, *envp));
	else if (ft_strcmp(argv[0], "pwd") == 0)
	{
		ft_putendl_fd((wd = getcwd(wd, 0)), 1);
		free(wd);	
		return (0);
	}
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (unset(argv[1], *envp));
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (echo(&argv[1]));
	else if (ft_strcmp(argv[0], "env") == 0)
		return (print_env(*envp, argv));
	else if (ft_strcmp(argv[0], "export") == 0)
		return (export(argv[1], envp));
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (exit_program(argv[1]));
	return (launch(argv));
}
