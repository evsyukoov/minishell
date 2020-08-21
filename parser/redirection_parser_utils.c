/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parser_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <ccarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 18:14:16 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/21 19:57:03 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**case1(char **argv, int arg_index)
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

char	**case2(char **argv, int arg_index, size_t len)
{
	int		i;
	char	**res;
	int		j;

	i = 0;
	j = 0;
	res = (char**)malloc(sizeof(char*) * (arg_index + 2));
	while (i < arg_index)
	{
		res[i] = ft_strdup(argv[i]);
		i++;
	}
	res[i] = (char*)malloc(len + 1);
	while (j < (int)len)
	{
		res[i][j] = argv[i][j];
		j++;
	}
	res[i][j] = '\0';
	i++;
	res[i] = NULL;
	return (res);
}

int		last_arg_len(char *arg, char redirection_type)
{
	int len;

	len = 0;
	while (*arg == redirection_type)
		arg++;
	while (arg[len] != redirection_type)
		len++;
	return (len);
}

char	*find_file_name(char *arg)
{
	while (*arg)
	{
		if (*arg == '>')
		{
			if (*(arg + 1) == '>')
				arg += 2;
			else if (*(arg + 1) != '>')
				arg += 1;
			break ;
		}
		arg++;
	}
	skip(&arg, '\'');
	skip(&arg, '\"');
	return (arg);
}
