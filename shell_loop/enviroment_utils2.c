/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 19:32:03 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/22 19:34:50 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_list(char **all_path)
{
	int i;

	i = 0;
	while (all_path[i])
		free(all_path[i++]);
	free(all_path);
	return (0);
}

int		free_all(char **all_path, char *path)
{
	free(path);
	free_list(all_path);
	return (1);
}
