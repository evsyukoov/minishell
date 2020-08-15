/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:08:59 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/15 21:26:15 by mcaptain         ###   ########.fr       */
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
	int char_type;

	args = 0;
	flag = 0;
	skip(&s, ' ');
	while (*s)
	{
		char_type = 0;
		if (*s == '\'' && ++char_type)
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
				push(lst, create_new_node(shell_split(argv_pipes[j]), PIPE, NULL, NONE));
			else
				push(lst, create_new_node(shell_split(argv_pipes[j]), COMMAND, NULL, NONE));
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
			push(&lst, create_new_node(shell_split(argv1[i]), COMMAND, NULL, NONE));
		i++;
	}
	free_arguments(&argv1);
	free(arg);
	return (parse_redirections(lst));
	//return lst;
}

char 	**case1(char **argv, int arg_index)
{
	int i;
	char **res;

	i = 0;
	res = (char**)malloc(sizeof(char*) * (arg_index + 1));
	while (i < arg_index)
	{
		res[i] = ft_strdup(argv[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

char 	**case2(char **argv, int arg_index, size_t len)
{
	int i;
	char **res;
	int j;

	i = 0;
	j = 0;
	res = (char**)malloc(sizeof(char*) * (arg_index + 2));
	while (i < arg_index)
	{
		res[i] = ft_strdup(argv[i]);
		i++;
	}
	res[i] = (char*)malloc(len + 1);
	while (j < (int)len)
	{
		res[i][j] = argv[i][j];
		j++;
	}
	res[i][j] = '\0';
	i++;
	res[i] = NULL;
	return (res);
}

int 	last_arg_len(char *arg)
{
	int len;

	len = 0;
	while (arg[len] != '>')
		len++;
	return (len);
}

char 	*find_file_name(char *arg)
{
	char *name;

	while (*arg)
	{
		if (*arg == '>')
		{
			if (*(arg + 1) == '>')
				arg += 2;
			else if (*(arg + 1) != '>')
				arg += 1;
			break;
		}
		arg++;
	}
	skip(&arg, '\'');
	skip(&arg, '\"');
	name = ft_strdup(arg);
	return (name);
}


//arg - та строчка, где встретился редирект
//argv - все строчки в ноде
//arg_index - индекс строки где встретился >

t_args 	*analize_redirection(char **argv, char *arg, int arg_index, t_args *old_node)
{
	t_args *node;

	node = NULL;
	// command > file
	if (ft_strlen(arg) == 1)
		node = create_new_node(case1(argv, arg_index), old_node->flag, argv[arg_index + 1], REWRITE);
	//command >> file
	else if (ft_strlen(arg) == 2 && str_endswith(arg, ">"))
		node = create_new_node(case1(argv, arg_index), old_node->flag, argv[arg_index + 1], WRITE);
	//command> file
	else if (str_endswith(arg, ">") && arg[ft_strlen(arg) - 2] != '>')
		node = create_new_node(case2(argv, arg_index, ft_strlen(argv[arg_index]) - 1), old_node->flag, argv[arg_index + 1], REWRITE);
	//command>> file
	else if (arg[ft_strlen(arg) - 1] == '>' && arg[ft_strlen(arg) - 2] == '>' && arg[ft_strlen(arg) - 3] != '>')
		node = create_new_node(case2(argv, arg_index, ft_strlen(argv[arg_index]) - 2), old_node->flag, argv[arg_index + 1], WRITE);
	//command>file
	else if (*(ft_strchr(arg, '>') + 1) != '>' && *(ft_strchr(arg, '>') - 1) != '>')
		node = create_new_node(case2(argv, arg_index, last_arg_len(arg)), old_node->flag, find_file_name(arg), WRITE);
	//command>>file
	else
		node = create_new_node(case2(argv, arg_index, last_arg_len(arg)), old_node->flag, find_file_name(arg), REWRITE);
	//free_arguments(&argv);
	return (node);
}



t_args 	*parse_redirections(t_args *lst)
{
	int i;
	char **argv;
	t_args *new_node;	//new_node - нода в которой будет хранится инфа об имени файла и типе перенаправления
	t_args *head;
	t_args *tmp;

	head = NULL;
	while(lst)
	{
		argv = (lst->args);
		i = 0;
		while (argv[i])
		{
			if (ft_strchr(argv[i], '>'))
			{
				tmp = lst;
				new_node = analize_redirection(argv, argv[i], i, lst);
				push(&head, new_node);
				free(tmp);
			}
			i++;
		}
		push(&head, lst);
		lst = lst->next;
		free_arguments(&argv);
	}
	head->next = NULL;
	return (head);
}

