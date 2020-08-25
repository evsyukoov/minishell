/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 22:16:20 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/25 15:56:11 by ccarl            ###   ########.fr       */
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
	argv_pipes = split(arg_pipe, '|');
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

int 		is_pipe(char *s)
{
	char q_type;

	while (*s)
	{
		q_type = quote_type(s);
		while (q_type)
		{
			skip_quotes(&s, q_type);
			q_type = quote_type(s);
		}
		if (*s == '|')
			return (1);
		s++;
	}
	return (0);
}

t_args		*create_list(char *arg, char **env)
{
	t_args	*lst;
	char	**argv1;
	int		i;

	i = 0;
	lst = NULL;
	argv1 = split(arg, ';');
	while (argv1[i])
	{
		if (is_pipe(argv1[i]))
			split_pipes(&lst, argv1[i], env);
		else
			push(&lst, create_new_node(
			shell_split(argv1[i], env), COMMAND, NULL));
		i++;
	}
	free_arguments(&argv1);
	return (parse_redirections(lst));
}

void		*parse_syntax_error(int flag)
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
						NULL, "syntax error near unexpected token ';'");
	g_last_code = 258;
	return (NULL);
}
