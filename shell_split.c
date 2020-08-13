/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:08:59 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/13 22:08:17 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		skip(char const **s, char del1, char del2)
{
	while ((**s == del1 || **s == del2) && **s)
		(*s)++;
}

static int		word_len(char const *s, char del1, char del2)
{
	int len;

	len = 0;
	while (s[len] != del1 && s[len] != del2 && s[len])
		len++;
	return (len);
}

static int		word_counter(char const *s, char del1, char del2)
{
	int words;

	words = 0;
	skip(&s, del1, del2);
	while (*s)
	{
		while (*s != del1 && *s != del2 && *s)
			s++;
		words++;
		skip(&s, del1, del2);
	}
	return (words);
}

char 		*concatination(char **argv, char *del, int *i)
{
	char *line;
	char *tmp;

	line = NULL;
	while (argv[*i]) {
			tmp = line;
			line = shell_join(line, argv[*i], *del);
			free(tmp);
			if (str_endswith(argv[*i], del))
			{
				(*i)++;
				break ;
			}
		(*i)++;
		}
	return (line);
}

int 		argv_len(char **argv)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while(argv[i])
	{
		if (str_startswith(argv[i], "'") || str_startswith(argv[i], "\""))
		{
			while (argv[i] && !str_endswith(argv[i], "'") && !str_endswith(argv[i], "\""))
				i++;
		}
		len++;
		i++;
	}
	return (len + 1);
}

t_args 		*init_node(int flag, char *arg)
{
	t_args *node;
	int		i;
	char	**final_argv;
	char 	**argv;
	int		j;

	argv = ft_split(arg,  ' ');
	final_argv = (char**)malloc(sizeof(char*) * argv_len(argv));
	i = 0;
	j = 0;
	while (argv[i])
	{
		if (str_startswith(argv[i], "'"))
			final_argv[j] = concatination(argv, "'", &i);
		else if (str_startswith(argv[i], "\""))
			final_argv[j] = concatination(argv, "\"", &i);
		else {
			final_argv[j] = ft_strdup(argv[i]);
			free(argv[i]);
			i++;
		}
		j++;
	}
	final_argv[j] = NULL;
	node = create_new_node(final_argv, flag);
	return (node);
}

t_args			*shell_split(char const *s, char del1, char del2)
{
	int		words;
	int		i;
	int		j;
	char	**res;
	t_args 	*lst_args;
	int 	flag;

	if (!s)
		return (0);
	lst_args = NULL;
	words = word_counter(s, del1, del2);
	if (!(res = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	i = 0;
	skip(&s, del1, del2);
	while (i < words)
	{
		if (!(res[i] = (char*)malloc(sizeof(char) * (word_len(s, del1, del2) + 1))))
			return (0);
		j = 0;
		while (*s)
		{
			flag = COMMAND;
			if (*s == del1 || *s == del2)
			{
				if (*s == del1)
					flag = COMMAND;
				else
					flag = PIPE;
				break ;
			}
			res[i][j++] = *s++;
		}
		res[i][j] = '\0';
		t_args *node = init_node(flag, res[i]);
		push(&lst_args, node);
		i++;
		skip(&s, del1, del2);
	}
	res[i] = NULL;
	return (lst_args);
}

