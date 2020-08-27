/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 22:16:20 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/27 18:22:56 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_args	*split_pipes(t_args **lst, char *arg_pipe, t_files **files)
{
	int		j;
	char	**argv_pipes;
	char	**splited;
	int		flag;

	j = 0;
	flag = PIPE;
	argv_pipes = split(arg_pipe, '|');
	if (!argv_pipes)
		return (0);
	while (argv_pipes[j])
	{
		*files = NULL;
		if (j == number_of_arguments(argv_pipes) - 1)
			flag = COMMAND;
		splited = split_arg(argv_pipes[j++], files);
		if (!splited)
		{
			free_args_list(lst);
			return (free_arguments(&argv_pipes));
		}
		push(lst, create_new_node(splited, flag, *files));
	}
	free_arguments(&argv_pipes);
	return (*lst);
}

void	*create_one_node(t_args **lst, t_files **files, char **argv1, int i)
{
	char **splited;

	if (is_pipe(argv1[i]))
	{
		if (!split_pipes(lst, argv1[i], files))
			return (free_arguments(&argv1));
	}
	else
	{
		splited = split_arg(argv1[i], files);
		if (!splited)
		{
			free_args_list(lst);
			return (free_arguments(&argv1));
		}
		push(lst, create_new_node(splited, COMMAND, *files));
	}
	return (*lst);
}

t_args	*create_list(char *arg)
{
	t_args	*lst;
	char	**argv1;
	int		i;
	t_files *files;

	i = 0;
	lst = NULL;
	argv1 = split(arg, ';');
	if (!argv1)
		return (0);
	while (argv1[i])
	{
		files = NULL;
		if (!(create_one_node(&lst, &files, argv1, i)))
			return (NULL);
		i++;
	}
	if (is_pipe_end(arg))
		change_option(lst);
	free_arguments(&argv1);
	return (lst);
}

void	*parse_syntax_error(int flag)
{
	if (flag == 3)
		print_error_log(
	"lsh: ", NULL, NULL, "syntax error near unexpected token '>'");
	else if (flag == 2)
		print_error_log("lsh: ", NULL,
		NULL, "syntax error near unexpected token 'newline'");
	else if (flag == 4)
		print_error_log("lsh: ", NULL,
						NULL, "syntax error near unexpected token '<'");
	else if (flag == 5)
		print_error_log("lsh: ", NULL,
						NULL, "syntax error near unexpected token ';;'");
	else if (flag == 6)
		print_error_log("lsh: ", NULL,
						NULL, "syntax error near unexpected token '|'");
	g_last_code = 258;
	return (NULL);
}
