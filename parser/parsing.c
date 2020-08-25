/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:40:29 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/25 22:54:56 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int 	count_slashes(char *s)
{
	int len;

	len = 0;
	while (s[len] == '\\')
		len++;
	len /= 2;
	return (len);
}

int 	is_spec_symbols_in_double(char *s)
{
	if ((*s == '$' && ft_isalnum(*(s + 1))) || *s == '\\' || (*s == '$' && (*(s + 1) == '?')))
		return (1);
	return (0);
}

void 	push_envir(char *s, t_str **head)
{
	char *name;
	char *envir;

	name = init_env_name(s);
	envir = get_env_var(name, g_env_copy);
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

char 	*analize_slash(char *s, t_str **head, int *ecranir)
{
	int slashes;

	slashes = 0;
	while (s[slashes] == '\\')
		slashes++;
	if (s[slashes] == '\"')
	{
		add_slashes(head, slashes / 2, '\"');
		s += slashes + 1;
	}
	else if (s[slashes] == '$')
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
			*ecranir = 1;
		}
	}
	return (s);
}

void 	parse_double_quotes(t_str **head, char **s)
{
	int ecranir;

	(*s)++;
	while (**s)
	{
		ecranir = 0;
		if (**s == '\"' && *(*s - 1) != '\\')
			break ;
		if (!is_spec_symbols_in_double(*s))
			add_to_str(head, **s, NULL);
		else
		{
			if (**s == '\\')
				*s = analize_slash(*s, head, &ecranir);
			if (**s == '$' && ft_isalnum(*(*s + 1)))
			{
				push_envir(*s, head);
				*s += env_len2(*s + 1);
			}
		}
		//if (!ecranir)
			(*s)++;
	}
}

void 	parse_simple_quotes(t_str **head, char **s)
{
	(*s)++;
	while (**s && **s != '\'')
	{
		add_to_str(head, **s, NULL);
		(*s)++;
	}
}

char 	**split_arg(char *s, char **env)
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
			if (*s == '\"' && *(s - 1) != '\\')
				parse_double_quotes(&str, &s);
			else if (*s == '\'' && *(s - 1) != '\\')
				parse_simple_quotes(&str, &s);
			else if (*s == '\\')
				s += count_slashes(s);
			else
				add_to_str(&str, *s, NULL);
			s++;
		}
		string = list_to_str(&str);
		add_to_list(&node, string);
		skip(&s, ' ');
	}
	return (node_to_argv(&node));
}
