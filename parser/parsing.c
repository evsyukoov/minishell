/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:40:29 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/27 15:37:41 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int 	is_spec_symbols(char *s)
{
	if ((*s == '$' && ft_isalnum(*(s + 1))) || (*s == '\\')
	|| (*s == '$' && (*(s + 1) == '?')) || *s == '\'' || *s == '\"')
		return (1);
	return (0);
}

void 	push_envir(char *s, t_str **head)
{
	char *name;
	char *envir;
	char *env_var;

	name = init_env_name(s);
	env_var = get_env_var(name, g_env_copy);
	if (env_var)
		envir = ft_strdup(env_var);
	else
		return ;
	if (envir)
		add_to_str(head, 0, envir);
	free(name);
}
void 	add_slashes(t_str **head, int count, char c)
{
	int i;

	i = 0;
	while (i < count)
	{
		add_to_str(head, '\\', NULL);
		i++;
	}
	if (c)
		add_to_str(head, c, NULL);
}

int 	count_slashes(char *s)
{
	int slashes;

	slashes = 0;
	while (s[slashes] == '\\')
		slashes++;
	return (slashes);
}

char	*ecranir_simple_quotes(char *s, t_str **head, int slashes, int flag)
{
	if (flag == 2)
	{
		add_slashes(head, slashes == 1 ? slashes :
						  (slashes % 2 == 0 ? slashes / 2 : slashes / 2 + 1), '\'');
		s += slashes + 1;
	}
	if (flag == 0)
	{
		add_slashes(head, slashes / 2, '\'');
		s += slashes + 1;
	}
	return (s);
}

char 	*parse_dollar(char *s, t_str **head)
{
	char *tmp;

	tmp = NULL;
	if (*s == '$' && *(s + 1) == '?')
	{
		tmp = ft_itoa(g_last_code);
		add_to_str(head, 0, tmp);
		s += 2;
	}
	if (*s == '$' && ft_isalnum(*(s + 1)))
	{
		push_envir(s, head);
		s += env_len2(s + 1) + 1;
	}
	return (s);
}

char 	*analize_slash(char *s, t_str **head, int flag)
{
	int slashes;

	slashes = count_slashes(s);
	if (s[slashes] == '\"')
	{
		add_slashes(head, slashes / 2, '\"');
		s += slashes + 1;
	}
	else if (s[slashes] == '$')
	{
		if (s[slashes + 1] == '?')
		{
			if (slashes % 2 == 0)
			{
				add_slashes(head, slashes / 2, 0);
				s += slashes;
			}
			else
			{
				add_slashes(head, slashes / 2, '$');
				s += slashes + 1;
			}
		}
		else if (slashes % 2 == 0)
		{
			add_slashes(head, slashes / 2, 0);
			s += slashes;
		}
		else
		{
			add_slashes(head, slashes / 2, '$');
			s += slashes + 1;
		}
	}
	else if (s[slashes] == '\'')
		s = ecranir_simple_quotes(s, head, slashes, flag);
	return (s);
}

void 	parse_double_quotes(t_str **head, char **s)
{
	(*s)++;
	while (**s)
	{
		if (**s == '\"' && *(*s - 1) != '\\' && (*s)++)
			break ;
		if (!is_spec_symbols(*s) || **s == '\'')
		{
			add_to_str(head, **s, NULL);
			(*s)++;
		}
		else
		{
			if (**s == '\\')
				*s = analize_slash(*s, head, 2);
			if (**s == '$')
				*s = parse_dollar(*s, head);
		}
	}
}

void 	parse_simple_quotes(t_str **head, char **s)
{
	(*s)++;
	while (**s)
	{
		if (**s == '\'' && *(*s - 1) != '\\' && (*s)++)
			break ;
		add_to_str(head, **s, NULL);
		(*s)++;
	}
}

char	*parse_home_path(char *s, t_str **head)
{
	char *res;

	res = ft_strdup(get_env_var("HOME", g_env_copy));
	if (*(s + 1) == '/' && ++s)
	{
		res = init_home_path(res, &s);
		add_to_str(head, 0, res);
	}
	else if ((*(s + 1) == ' ' || !*(s + 1)) && ++s)
		add_to_str(head, 0, res);
	else
	{
		add_to_str(head, '~', 0);
		s++;
		free(res);
	}
	return (s);
}

int 	is_redirections(char *s)
{
	if (*s == '>' || *s == '<')
		return (1);
	return (0);
}

int		check_for_newline_error(char *s)
{
	while (*s && *s == ' ')
		s++;
	if (!*s)
		return (0);
	return (1);
}

char 	*count_redirections(char *s, int *count, char type)
{
	while (*s == type)
	{
		s++;
		(*count)++;
	}
	return (s);
}

int 	type_of_redirection(char **s)
{
	int count;

	count = 0;
	*s = count_redirections(*s, &count, '>');
	if (!check_for_newline_error(*s))
		return ((int)parse_syntax_error(2));
	if (count > 2)
		return ((int)parse_syntax_error(3));
	if (count == 2)
		return (WRITE);
	if (count == 1)
		return (REWRITE);
	count = 0;
	*s = count_redirections(*s, &count, '<');
	if (!check_for_newline_error(*s))
		return ((int)parse_syntax_error(2));
	if (count > 1)
		return ((int)parse_syntax_error(4));
	if (count == 1)
		return (REVERSE);
}

void 	free_files(t_files **files)
{
	t_files *tmp;

	while (*files)
	{
		tmp = *files;
		free((*files)->name);
		*files = (*files)->next;
		free(tmp);
	}
}

void 	free_nodes(t_node **head)
{
	t_node *tmp;

	while (*head)
	{
		tmp = *head;
		free((*head)->str);
		*head = (*head)->next;
		free(tmp);
	}
}

char 	*parse_redirect(char *s, t_files **files)
{
	t_str *str;
	int flag;

	str = NULL;
	flag = type_of_redirection(&s);
	if (!flag)
	{
		free_files(files);
		return (0);
	}
	skip(&s,' ');
	while (*s && *s != ' ' && *s != '>' && *s != '<')
		s = parsing(s, &str);
	push_redirect(files, new_redirection(list_to_str(&str), flag));
	return (s);
}

char 	*wait_for_next_redirect(char *s)
{
	skip (&s, ' ');
	while (*s && !is_redirections(s))
		s++;
	return (s);
}

char 	*parsing(char *s, t_str **str)
{
	if (*s == '~')
		s = parse_home_path(s, str);
	if (*s == '\"' && *(s - 1) != '\\')
		parse_double_quotes(str, &s);
	if (*s == '\'' && *(s - 1) != '\\')
		parse_simple_quotes(str, &s);
	if (*s == '\\')
		s = analize_slash(s, str, 0);
	if (*s == '$')
		s = parse_dollar(s, str);
	if (!is_spec_symbols(s) && *s && *s != ' ' && !is_redirections(s))
	{
		add_to_str(str, *s, NULL);
		s++;
	}
	return (s);
}

int		redirection_parser_loop(char **s, t_files **files, t_str *str, t_node **node)
{
	int flag;

	flag = 0;
	if (is_redirections(*s) && ++flag)
	{
		if (str)
			add_to_list(node, list_to_str(&str));
		while (**s)
		{
			if (!(*s = parse_redirect(*s, files)))
			{
				free_nodes(node);
				return (-1);
			}
			*s = wait_for_next_redirect(*s);
		}
	}
	return (flag);
}

char 	**split_arg(char *s, t_files **files)
{
	t_node	*node;
	t_str	*str;
	int		flag;

	node = NULL;
	skip(&s, ' ');
	while (*s)
	{
		str = NULL;
		while (*s && *s != ' ')
		{
			flag = redirection_parser_loop(&s, files, str, &node);
			if (flag == -1)
				return (0);
			if (flag)
				return (node_to_argv(&node));
			s = parsing(s, &str);
		}
		add_to_list(&node, list_to_str(&str));
		skip(&s, ' ');
	}
	return (node_to_argv(&node));
}

int		check(t_args *lst)
{
	int		i;
	t_args	*begin;
	int		flag;

	begin = lst;
	while (lst)
	{
		i = 0;
		while (lst->args[i])
		{
			if (ft_strchr(lst->args[i], '>') || ft_strchr(lst->args[i], '<'))
			{
				if ((flag = check_error_redirections(lst->args, i)))
				{
					parse_syntax_error(flag);
					free_args_list(&begin);
					return (0);
				}
			}
			i++;
		}
		lst = lst->next;
	}
	return (1);
}
