/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 22:44:33 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/26 18:45:22 by ccarl            ###   ########.fr       */
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
