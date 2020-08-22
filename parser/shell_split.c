/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:08:59 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/22 21:24:12 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_char(char *arg, char c)
{
	char	*res;
	int		i;

	i = 0;
	if (!(res = (char*)malloc(ft_strlen(arg) + 2)))
		return (0);
	while (*arg)
		res[i++] = *arg++;
	res[i++] = c;
	res[i] = '\0';
	return (res);
}

int		is_dollar_symbol(char *arg)
{
	if (*arg == '$' && (!ft_isalnum(*(arg + 1)) || *(arg + 1) == ' '))
		return (1);
	return (0);
}

char	*init_arg(char **arg, char **env, t_split var)
{
	char	*res;

	if (!(res = replace_bash_symbols(&arg, env)))
	{
		var.q_type = quote_type(*arg);
		var.arg_len = argument_len(*arg, var.q_type);
		if (!(res = (char *)malloc(var.arg_len + 1)))
			return (0);
		var.j = 0;
		skip(arg, var.q_type);
		while (var.j < var.arg_len && **arg)
			res[var.j++] = *(*arg)++;
		res[var.j] = '\0';
		skip(arg, var.q_type);
		skip(arg, ' ');
	}
	return (res);
}
