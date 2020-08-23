/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 18:10:41 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/23 15:51:35 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int 	get_files(char **argv, char *arg, int arg_index, t_files **head)
{
	t_files *node;

	node = NULL;
	if (!argv[arg_index + 1])
		return (0);
	if (ft_strlen(arg) == 1 && *arg == '>')
		node = new_redirection(argv[arg_index + 1], REWRITE);
	else if (ft_strlen(arg) == 1 && *arg == '<')
		node = new_redirection(argv[arg_index + 1], REVERSE);
	else if (ft_strlen(arg) == 2 && *arg == '>' && *(arg + 1) == '>')
		node = new_redirection(argv[arg_index + 1], WRITE);
	if (node)
		push_redirect(head, node);
	return (1);
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
	char **arguments;
	t_files *files;

	i = 0;
	arguments = NULL;
	files = NULL;
	while (lst->args[i])
	{
		if (ft_strchr(lst->args[i], '>') || ft_strchr(lst->args[i], '<') )
		{
			if (!arguments)
				arguments = get_commands(lst->args, i);
			if (!(get_files(lst->args, lst->args[i], i, &files)))
				return (2);
		}
		i++;
	}
	if (files)
	{
		new_node = create_new_node(arguments, lst->flag, files);
		push(head, new_node);
		return (1);
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
			return (parse_syntax_error(1));
		flag = check_node_for_redirection(lst, &head);
		if (!flag)
			push(&head, create_new_node(lst->args, lst->flag,
			lst->files));
		else if (flag == 2)
			return (parse_syntax_error(2));
		else
			free_arguments(&lst->args);
		lst = lst->next;
		free(tmp);
	}
	return (head);
}
