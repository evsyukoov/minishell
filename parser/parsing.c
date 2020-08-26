/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:40:29 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/26 20:37:13 by ccarl            ###   ########.fr       */
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

	name = init_env_name(s);
	envir = ft_strdup(get_env_var(name, g_env_copy));
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

char 	**split_arg(char *s)
{
	t_node	*node;
	t_str	*str;
	char 	*string;

	node = NULL;
	skip(&s, ' ');
	while (*s)
	{
		str = NULL;
		while (*s && *s != ' ')
		{
			if (*s == '~')
				s = parse_home_path(s, &str);
			if (*s == '\"' && *(s - 1) != '\\')
				parse_double_quotes(&str, &s);
			if (*s == '\'' && *(s - 1) != '\\')
				parse_simple_quotes(&str, &s);
			if (*s == '\\')
				s = analize_slash(s, &str, 0);
			if (*s == '$')
				s = parse_dollar(s, &str);
			if (!is_spec_symbols(s) && *s && *s != ' ')
			{
				add_to_str(&str, *s, NULL);
				s++;
			}
		}
		string = list_to_str(&str);
		add_to_list(&node, string);
		skip(&s, ' ');
	}
	return (node_to_argv(&node));
}
