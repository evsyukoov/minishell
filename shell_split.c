/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:08:59 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/15 15:48:20 by ccarl            ###   ########.fr       */
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

void 	split_pipes(t_args **lst, char *arg_pipe)
{
	int j;
	char **argv_pipes;
	int num_of_args;

	j = 0;
	argv_pipes = ft_split(arg_pipe, '|');
	num_of_args = number_of_arguments(argv_pipes);
	while (argv_pipes[j])
	{
		{
			if (j < num_of_args - 1)
				push(lst, create_new_node(shell_split(argv_pipes[j]), PIPE));
			else
				push(lst, create_new_node(shell_split(argv_pipes[j]), COMMAND));
			j++;
		}
	}
	free_arguments(&argv_pipes);
}

t_args 	*create_list(char *arg)
{
	t_args *lst;
	char **argv1;
	int i;

	i = 0;
	lst = NULL;
	argv1 = ft_split(arg, ';');
	while(argv1[i])
	{
		if (ft_strchr(argv1[i], '|'))
			split_pipes(&lst, argv1[i]);
		else
			push(&lst, create_new_node(shell_split(argv1[i]), COMMAND));
		i++;
	}
	free_arguments(&argv1);
	free(arg);
	return (lst);
}

/*t_args 	*modify_node(char **argv, int index)
{
	int i;
	t_args *new_node;
	char 	**new_argv;

	i = 0;
	new_argv = (char**)malloc(sizeof(char*) * (number_of_arguments(argv)));
	while (argv[i])
	{
		if (i != index)
		{
			new_argv[i] = ft_strdup(argv[i]);
		}
		i++;
	}

}

t_args 	*find_redirections(t_args *lst)
{
	int i;
	int j;
	char **argv;

	while(lst)
	{
		argv = (lst->args);
		j = 0;
		while (argv[i])
		{
			if (argv[i][0] == '<' && argv[i][1] != '<')
			{

			}
			else if (argv[i][0] == '<' && argv[i][1] == '<' && argv[i][2] != '<')
			{

			}
		}
		lst = lst->next;
	}
}*/

