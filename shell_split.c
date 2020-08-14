/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:08:59 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/14 22:18:52 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		skip(char **s, char del)
{
	while (**s == del && **s)
		(*s)++;
}

static int		argument_len(char *s, char quote)
{
	int len;
	int flag;

	len = 0;
	while (*s && *s != ' ')
	{
		if (*s == quote)
		{
			while(*s && *s == quote)
				s++;
			while (*s && *s != quote)
			{
				s++;
				len++;
			}
			if (*s == quote)
				break ;
		}
		else
		{
			s++;
			len++;
		}
	}
	return (len);
}

static int     find_close_quote(char **s, char quote, int *args)
{
	while (**s && **s == quote)
		(*s)++;
	while (**s && **s != quote)
		(*s)++;
	(*args)++;
	return (1);
}

static int		arguments_counter(char *s)
{
	int args;
	int flag;

	args = 0;
	flag = 0;
	skip(&s, ' ');
	while (*s)
	{
		if (*s == '\'')
			flag = find_close_quote(&s, '\'', &args);
		else if (*s == '\"')
			flag = find_close_quote(&s, '\"', &args);
		while (*s && *s != ' ')
			s++;
		if (!flag)
			args++;
		skip(&s, ' ');
		flag = 0;
	}
	return (args);
}

char	quote_type(char *arg)
{
	if (*arg == '\"')
		return ('\"');
	else if (*arg == '\'')
		return('\'');
	else
		return ('\0');
}

char	**shell_split(char *arg)
{
	t_split var;
	char **res;

	var.args = arguments_counter(arg);
	var.i = 0;
	if (!(res = (char**)malloc(sizeof(char*) * (var.args + 1))))
		return (0);
	skip(&arg, ' ');
	while (var.i < var.args)
	{
		var.q_type = quote_type(arg);
		var.arg_len = argument_len(arg, var.q_type);
		res[var.i] = (char*)malloc(var.arg_len + 1);
		var.j = 0;
		while (var.j < var.arg_len && *arg)
		{
			skip(&arg, var.q_type);
			res[var.i][var.j++] = *arg++;
		}
		res[var.i++][var.j] = '\0';
		skip(&arg, var.q_type);
		skip(&arg, ' ');
	}
	res[var.i] = NULL;
	return (res);
}

int 	number_of_arguments(char **argv)
{
	int j;

	j = 0;
	while (argv[j])
		j++;
	return (j);
}

t_args 	*create_list(char *arg)
{
	t_args *lst;
	char **argv1;
	char **argv2;
	int i;
	int j;

	i = 0;
	lst = NULL;
	argv1 = ft_split(arg, ';');
	while(argv1[i])
	{
		if (ft_strchr(argv1[i], '|'))
		{
			argv2 = ft_split(argv1[i], '|');
			j = 0;
			while (argv2[j])
			{
				if (j < number_of_arguments(argv2) - 1)
					push(&lst, create_new_node(shell_split(argv2[j]), PIPE));
				else
					push(&lst, create_new_node(shell_split(argv2[j]), COMMAND));
				j++;
			}
		}
		else
			push(&lst, create_new_node(shell_split(argv1[i]), COMMAND));
		i++;
	}
	//НАДО РАЗОБРАТЬСЯ С free!!!!!!!!!
	//free_arguments(argv1);
	//free_arguments(argv2);
	return (lst);
}

