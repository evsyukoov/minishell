/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 18:10:41 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/22 13:59:48 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	*condition2(char **argv, char *arg, int i, t_args *old_node)
{
	t_args *node;

	node = NULL;
	if (str_endswith(arg, ">") && arg[ft_strlen(arg) - 2] != '>')
		node = create_new_node(case2(argv, i,
		ft_strlen(argv[i]) - 1), old_node->flag,
		argv[i + 1], REWRITE);
	else if (arg[ft_strlen(arg) - 1] == '>' && arg[ft_strlen(arg) - 2] == '>'
	&& arg[ft_strlen(arg) - 3] != '>')
		node = create_new_node(case2(argv, i, ft_strlen(argv[i]) - 2),
		old_node->flag, argv[i + 1], 1);
	else if (str_startswith(arg, ">") && *(arg + 1) != '>')
		node = create_new_node(case1(argv, i),
		old_node->flag, arg + 1, 0);
	else if (str_startswith(arg, ">") && *(arg + 1) == '>')
		node = create_new_node(case1(argv, i),
		old_node->flag, arg + 2, 1);
	else if (*(ft_strchr(arg, '>') + 1) != '>'
	&& *(ft_strchr(arg, '>') - 1) != '>')
		node = create_new_node(case2(argv, i, last_arg_len(arg, '>')),
		old_node->flag, find_file_name(arg), 0);
	else
		node = create_new_node(case2(argv, i, last_arg_len(arg, '>')),
		old_node->flag, find_file_name(arg), 1);
	return (node);
}

t_args	*analize_redirection(char **argv,
char *arg, int arg_index, t_args *old_node)
{
	t_args *node;

	node = NULL;
	if (ft_strlen(arg) == 1 && *arg == '>')
		node = create_new_node(case1(argv, arg_index),
		old_node->flag, argv[arg_index + 1], REWRITE);
	else if (ft_strlen(arg) == 1 && *arg == '<')
		node = create_new_node(case1(argv, arg_index),
		old_node->flag, argv[arg_index + 1], REVERSE);
	else if (str_endswith(arg, "<"))
		node = create_new_node(case2(argv, arg_index,
		ft_strlen(argv[arg_index]) - 1), old_node->flag,
		argv[arg_index + 1], REVERSE);
	else if (ft_strchr(arg, '<'))
		node = create_new_node(case2(argv, arg_index, last_arg_len(arg, '<')),
		old_node->flag, ft_strchr(arg, '<') + 1, REVERSE);
	else if (ft_strlen(arg) == 2 && str_endswith(arg, ">"))
		node = create_new_node(case1(argv, arg_index),
		old_node->flag, argv[arg_index + 1], WRITE);
	else
		node = condition2(argv, arg, arg_index, old_node);
	return (node);
}

int		check_error_redirections(char **argv)
{
	int i;
	int j;
	int count1;

	i = 0;
	while (argv[i])
	{
		j = 0;
		count1 = 0;
		if (argv[i + 1] && !ft_strcmp(argv[i], ">") &&
			(!ft_strcmp(argv[i + 1], ">") || !ft_strcmp(argv[i + 1], ">>")))
			return (1);
		while (argv[i][j])
		{
			if (argv[i][j] == '>' || argv[i][j] == '<')
				count1++;
			if (count1 > 2)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int		check_node_for_redirection(t_args *lst, t_args **head)
{
	int		i;
	t_args	*new_node;

	i = 0;
	while (lst->args[i])
	{
		if (ft_strchr(lst->args[i], '>') || ft_strchr(lst->args[i], '<'))
		{
			new_node = analize_redirection(lst->args, lst->args[i], i, lst);
			push(head, new_node);
			free_arguments(&lst->args);
			return (1);
		}
		i++;
	}
	return (0);
}

t_args	*parse_redirections(t_args *lst)
{
	t_args	*tmp;
	t_args	*head;
	int		flag;

	head = NULL;
	while (lst)
	{
		tmp = lst;
		if (check_error_redirections(lst->args))
			return (parse_syntax_error());
		flag = check_node_for_redirection(lst, &head);
		if (!flag)
			push(&head, create_new_node(lst->args, lst->flag,
			lst->file_path, lst->file_option));
		lst = lst->next;
		free(tmp);
	}
	return (head);
}
