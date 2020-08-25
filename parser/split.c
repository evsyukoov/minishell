/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 18:10:41 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/25 01:07:53 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

char	quote_type(char *arg)
{
	if (*arg == '\"')
		return ('\"');
	else if (*arg == '\'')
		return ('\'');
	else
		return ('\0');
}

static void		skip_d(char const **s, char delimetr)
{
	while (**s == delimetr && **s)
		(*s)++;
}

static int		word_len(char const *s, char delimetr)
{
	int len;

	len = 0;
	while (s[len] != delimetr && s[len])
		len++;  
	return (len);
}

void 	skip_quotes(char **s, char q_type)
{
	if (q_type)
	{
		(*s)++;
		while (**s && **s != q_type)
			(*s)++;
		(*s)++;
	}
}

int		word_counter(char *s, char delimetr)
{
	int words;
	char q_type;

	words = 0;
	if (*s == delimetr)
	{
	//	parse_syntax_error(5);
		return (-1);
	}
	while (*s)
	{
		q_type = quote_type(s);
		if (q_type)
		{
			skip_quotes(&s, q_type);
			s++;
		}
		printf("s = %s\n", s);
		if (*s == delimetr)
		{
			s++;
			words++;
		}
		else if (!*(s + 1))
			words++;
		s++;
	}
	return (words);
}

/*char			**ft_split(char const *s, char c)
{
	int		words;
	int		i;
	int		j;
	char	**res;

	if (!s)
		return (0);
	words = word_counter(s, c);
	if (!(res = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	i = 0;
	skip(&s, c);
	while (i < words)
	{
		if (!(res[i] = (char*)malloc(sizeof(char) * (word_len(s, c) + 1))))
			return (0);
		j = 0;
		while (*s != c && *s)
			res[i][j++] = *s++;
		res[i][j] = '\0';
		i++;
		skip(&s, c);
	}
	res[i] = NULL;
	return (res);
}*/

int 	main(void)
{
	char test[1000] = "ascasfsa\"aefqfeqq\"";
	printf("res = %d\n", word_counter(test, ';'));
}


