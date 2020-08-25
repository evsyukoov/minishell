/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_parser_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 21:45:04 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/24 18:22:44 by ccarl            ###   ########.fr       */
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

char	*get_environment_with_quotes(char *arg, char **env, int begin_len)
{
	char	*res;

	res = get_environment_string(arg, env, begin_len);
	arg += env_len2(arg);
	res = lines26(arg, env, res);
	return (res);
}
