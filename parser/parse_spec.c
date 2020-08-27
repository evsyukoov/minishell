/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 17:45:08 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/27 18:00:05 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		is_spec_symbols(char *s)
{
	if ((*s == '$' && ft_isalnum(*(s + 1))) || (*s == '\\')
		|| (*s == '$' && (*(s + 1) == '?')) || *s == '\'' || *s == '\"')
		return (1);
	return (0);
}

void	push_envir(char *s, t_str **head)
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

char	*parse_dollar(char *s, t_str **head)
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
