/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 22:16:20 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/23 15:51:32 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		**shell_split(char *arg, char **env)
{
	t_split	var;
	char	**res;

	var.args = arguments_counter(arg);
	var.i = 0;
	if (!(res = (char **)malloc(sizeof(char *) * (var.args + 1))))
		return (0);
	skip(&arg, ' ');
	while (var.i < var.args)
	{
		res[var.i] = init_arg(&arg, env, var);
		var.i++;
	}
	res[var.i] = NULL;
	return (res);
}

int			number_of_arguments(char **argv)
{
	int j;

	j = 0;
	while (argv[j])
		j++;
	return (j);
}

void		split_pipes(t_args **lst, char *arg_pipe, char **env)
{
	int		j;
	char	**argv_pipes;
	int		num_of_args;

	j = 0;
	argv_pipes = ft_split(arg_pipe, '|');
	num_of_args = number_of_arguments(argv_pipes);
	while (argv_pipes[j])
	{
		{
			if (j < num_of_args - 1)
				push(lst, create_new_node(
				shell_split(argv_pipes[j], env), PIPE, NULL));
			else
				push(lst, create_new_node(
				shell_split(argv_pipes[j], env), COMMAND, NULL));
			j++;
		}
	}
	free_arguments(&argv_pipes);
}

t_args		*create_list(char *arg, char **env)
{
	t_args	*lst;
	char	**argv1;
	int		i;

	i = 0;
	lst = NULL;
	argv1 = ft_split(arg, ';');
	while (argv1[i])
	{
		if (ft_strchr(argv1[i], '|'))
			split_pipes(&lst, argv1[i], env);
		else
			push(&lst, create_new_node(
			shell_split(argv1[i], env), COMMAND, NULL));
		i++;
	}
	free_arguments(&argv1);
	return (parse_redirections(lst));
	//return (lst);
}

void		*parse_syntax_error(int flag)
{
	if (flag)
	print_error_log(
	"lsh: ", NULL, NULL, "syntax error near unexpected token '>'");
	else
		print_error_log(
				"lsh: ", NULL, NULL, "syntax error near unexpected token 'newline'");
	last_code = 258;
	return (NULL);
}
