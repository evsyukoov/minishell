/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_parser_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 21:45:04 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/23 19:32:53 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*lines26(char *arg, char **env, char *res)
{
	char	*s2;
	char	*tmp;

	while (*arg && *arg != '\"')
	{
		if (*arg != '$' || is_dollar_symbol(arg))
			res = join_char(res, *arg);
		else
		{
			s2 = get_environment_string(arg, env, 0);
			tmp = res;
			res = ft_strjoin(res, s2);
			free(s2);
			free(tmp);
			arg += env_len2(arg);
			if (*arg != '\"')
				res = join_char(res, *arg);
			else
				break ;
		}
		arg++;
	}
	return (res);
}

char	*get_environment_with_quotes(char *arg, char **env, int begin_len)
{
	char	*res;

	res = get_environment_string(arg, env, begin_len);
	arg += env_len2(arg);
	res = lines26(arg, env, res);
	return (res);
}
