/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parser_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 18:14:16 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/22 13:59:45 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_commands(char **argv, int arg_index)
{
	int		i;
	char	**res;

	i = 0;
	res = (char**)malloc(sizeof(char*) * (arg_index + 1));
	while (i < arg_index)
	{
		res[i] = ft_strdup(argv[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}
