/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:00:38 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/27 18:08:37 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		parse_error(char type)
{
	int flag;

	flag = 0;
	if (type == ';')
		flag = 5;
	else if (type == '|')
		flag = 6;
	parse_syntax_error(flag);
	return (-1);
}

int		skip_quotes(char **s, char q_type)
{
	int len;

	len = 0;
	if (q_type)
	{
		(*s)++;
		len++;
		while (**s && **s != q_type)
		{
			(*s)++;
			len++;
			if (**s == q_type && *(*s - 1) == '\\')
			{
				(*s)++;
				len++;
			}
		}
		(*s)++;
		len++;
	}
	return (len);
}

int		word_len(char *str, char delimetr)
{
	int		len;
	char	q_type;

	len = 0;
	while (*str && *str != delimetr)
	{
		q_type = quote_type(str);
		while (q_type)
		{
			len += skip_quotes(&str, q_type);
			q_type = quote_type(str);
		}
		if (*str == delimetr)
			return (len);
		str++;
		len++;
	}
	return (len);
}

int		word_counter(char *str, char delimetr)
{
	int		words;
	char	q_type;

	words = 0;
	if (*str == delimetr)
		return (parse_error(*str));
	while (*str)
	{
		q_type = quote_type(str);
		while (q_type)
		{
			skip_quotes(&str, q_type);
			q_type = quote_type(str);
		}
		if (*str == delimetr)
		{
			if (*(str + 1) == delimetr)
				return (parse_error(delimetr));
			words++;
		}
		else if (!*(str + 1))
			words++;
		str++;
	}
	return (words);
}

char	**split(char *s, char c)
{
	int		words;
	int		i;
	int		j;
	char	**res;
	int		len;

	if ((words = word_counter(s, c)) == -1)
		return (0);
	if (!(res = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	i = 0;
	while (i < words)
	{
		len = word_len(s, c);
		if (!(res[i] = (char*)malloc(sizeof(char) * (len + 1))))
			return (0);
		j = 0;
		while (j < len)
			res[i][j++] = *s++;
		res[i][j] = '\0';
		i++;
		s++;
	}
	res[i] = NULL;
	return (res);
}
