/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:58:31 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/12 17:20:17 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 		is_delimetr(char c)
{
	if (c == ' ' || c == ';' || c == '|')
		return (1);
	return (0);
}

// создадим лист в котором каждая нода это двухмерный массив(строк)
// в этом двухмерном массиве первая строка это команда, а последующие это аргументы это команды
// например cd /Users;pwd дадут первая нода - args[0] = "cd" args[1] = "/Users" , вторая нода args[0] = "pwd"

void 		skip(char **line)
{
	if (is_delimetr(**line))
		(*line)++;
}

//находим позицию разделителя

int 		find_del_position(int i, char *line)
{
	while (line[i])
	{
		if (line[i] == ';')
			return (i);
		i++;
	}
	return (i);
}

// char 		**split_args(char *line)
// {
// 	char **args;
// 	int	i;
// 	char *tmp;

// 	args = ft_split(line, ' ');
// 	free(line);
// 	i = 0;
// 	while (args[i])
// 	{
// 		if (ft_str_startswith(args[i],"\""))
// 			while(!str_endswith(args[i], "\""))
// 			{
				
// 			}

// 	}

// }

int			command_len(char *line)
{
	int i;

	i = 0;
	while (!is_delimetr(*line))
		i++;
	return (i);
}

t_args		*create_list(char *line)
{
	t_args	*lst;
	int		begin;
	int		end;
	char 	*arg;

	begin = 0;
	lst = NULL;
	while (1)
	{
		end = find_del_position(begin, line);
		arg = ft_substr(line, begin, end - begin);
		printf("arg = %s$\n", arg);
		begin = end + 1;
		push(&lst, new_node(arg));
		if (!line[end])
			break;
	}
	//free(line);
	return (lst);
}



