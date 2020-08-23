/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:31:10 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/23 15:49:08 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*init_home_path(char *tilda, char **arg)
{
	char	*full_path;
	int		i;
	int		j;

	i = 0;
	while ((*arg)[i] && (*arg)[i] != ' ')
		i++;
	full_path = (char*)malloc(i + 1 + ft_strlen(tilda));
	ft_strlcpy(full_path, tilda, ft_strlen(tilda));
	j = (int)ft_strlen(tilda) - 1;
	while (**arg && **arg != ' ' && **arg != '\"')
		full_path[j++] = *(*arg)++;
	full_path[j] = '\0';
	free(tilda);
	return (full_path);
}
