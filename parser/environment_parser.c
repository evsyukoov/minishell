/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 21:45:04 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/22 21:21:16 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_environment_string(char *arg, char **env, int begin_len)
{
	char *env_name;
	char *env_var;
	char *res;
	char *begin;

	begin = NULL;
	env_name = init_env_name(arg);
	env_var = get_env_var(env_name, env);
	if (!env_var)
		res = ft_strdup("\0");
	else
		res = get_env_var(env_name, env);
	begin = get_begin_string(arg, begin_len);
	if (begin)
		res = ft_strjoin(begin, res);
	free(begin);
	free(env_name);
	return (res);
}

char	*get_environment_with_quotes(char *arg, char **env, int begin_len)
{
	char *res;
	char *tmp;
	char *s2;

	res = get_environment_string(arg, env, begin_len);
	arg += env_len2(arg);
	while (*arg && *arg != '\"')
	{
		tmp = res;
		if (*arg != '$' || is_dollar_symbol(arg))
			res = join_char(res, *arg);
		else
		{
			s2 = get_environment_string(arg, env, 0);
			res = ft_strjoin(res, s2);
			free(s2);
			arg += env_len2(arg);
			if (*arg == '\'')
				res = join_char(res, *arg);
		}
		free(tmp);
		arg++;
	}
	return (res);
}

char	*get_environment(char ***arg, char **env, int flag)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	if (flag)
		i++;
	while ((**arg)[i] && (((**arg)[i] != ' ' && flag == 0)
	|| ((**arg)[i] != '\"' && flag == 1)))
	{
		if (!flag && (**arg)[i] == '$')
		{
			res = get_environment_string(**arg + i, env, i);
			**arg += i + env_len2(**arg + i);
			break ;
		}
		else if (flag && (**arg)[i] == '$')
		{
			res = get_environment_with_quotes(**arg + i, env, i - 1);
			**arg += i + quotes_size(**arg + i);
			break ;
		}
		i++;
	}
	return (res);
}

char	*analize_env(char **arg, char **env)
{
	char	*res;
	int		flag;

	flag = 0;
	res = NULL;
	if (**arg == '\'')
		return (0);
	if (**arg == '\"')
		flag = 1;
	if (!(res = get_environment(&arg, env, flag)))
		return (0);
	return (res);
}

char	*replace_bash_symbols(char ***arg, char **env)
{
	char *res;

	res = NULL;
	if (***arg == '$' && *(**arg + 1) == '?')
	{
		res = ft_itoa(last_code);
		**arg += 2;
		skip(*arg, ' ');
	}
	else if (is_dollar_symbol(**arg))
		return (0);
	else if ((res = analize_env(*arg, env)))
		skip_env(*arg);
	else if (***arg == '~' && ++(**arg))
	{
		res = ft_strdup(get_env_var("HOME", env));
		skip(*arg, ' ');
	}
	return (res);
}
