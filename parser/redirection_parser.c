/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 18:10:41 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/24 18:15:54 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		get_files(char **argv, char *arg, int arg_index, t_files **head)
{
	t_files *node;

	node = NULL;
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

int		check_error_redirections(char **argv, int i)
{
	if (!argv[i + 1])
		return (2);
	if (ft_strlen(argv[i]) == 3 && *argv[i] == '>' && *(argv[i] + 1) == '>'
	&& *(argv[i] + 2) == '>')
		return (3);
	else if (ft_strlen(argv[i]) == 2 && *argv[i] == '>'
	&& *(argv[i] + 1) == '<')
		return (4);
	return (0);
}

int		another26line(char ***arguments, t_args *lst, int i, t_files **files)
{
	if (!(*arguments))
		*arguments = get_commands(lst->args, i);
	if (!(get_files(lst->args, lst->args[i], i, files)))
		return (2);
	return (0);
}

int		check_node_for_redirection(t_args *lst, t_args **head)
{
	int		i;
	char	**arguments;
	t_files	*files;

	i = 0;
	arguments = NULL;
	files = NULL;
	while (lst->args[i])
	{
		if (ft_strchr(lst->args[i], '>') || ft_strchr(lst->args[i], '<'))
		{
			if (another26line(&arguments, lst, i, &files))
				return (2);
		}
		i++;
	}
	if (files)
	{
		push(head, create_new_node(arguments, lst->flag, files));
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
	if (!check(lst))
		return (NULL);
	while (lst)
	{
		tmp = lst;
		flag = check_node_for_redirection(lst, &head);
		if (!flag)
			push(&head, create_new_node(lst->args, lst->flag,
			lst->files));
		else
			free_arguments(&lst->args);
		lst = lst->next;
		free(tmp);
	}
	return (head);
}
