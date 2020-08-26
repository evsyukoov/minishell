/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 22:44:33 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/26 23:25:49 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	skip(char **s, char del)
{
	while (**s == del && **s)
		(*s)++;
}

char	quote_type(char *arg)
{
	if (*arg == '\"' && *(arg - 1) != '\\')
		return ('\"');
	else if (*arg == '\'' && *(arg - 1) != '\\')
		return ('\'');
	else
		return ('\0');
}

int		env_len2(char *arg)
{
	int i;

	i = 0;
	while (arg[i] && arg[i] != ' ' && arg[i] != '\'' && arg[i] != '\"'
		   && arg[i] != '\\' && arg[i] != '$' && arg[i] != '=' && arg[i] != ';' && arg[i] != '|')
		i++;
	return (i);
}

char	*init_env_name(char *arg)
{
	char	*name;
	int		i;
	int len;

	arg += 1;
	len = env_len2(arg);
	name = (char*)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
		name[i++] = *arg++;
	name[i] = '\0';
	return (name);
}

char	*init_home_path(char *tilda, char **arg)
{
	char	*full_path;
	int		i;
	int		j;

	i = 0;
	while ((*arg)[i] && (*arg)[i] != ' ')
		i++;
	full_path = (char*)malloc(i + 1 + ft_strlen(tilda));
	ft_strlcpy(full_path, tilda, ft_strlen(tilda) + 1);
	j = (int)ft_strlen(tilda);
	while (**arg && **arg != ' ' && **arg != '\"')
		full_path[j++] = *(*arg)++;
	full_path[j] = '\0';
	free(tilda);
	return (full_path);
}
