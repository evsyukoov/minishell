/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 22:44:33 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/23 15:49:24 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	skip(char **s, char del)
{
	while (**s == del && **s)
		(*s)++;
}

int		argument_len(char *s, char quote)
{
	int len;

	len = 0;
	while (*s && *s != ' ')
	{
		if (*s == quote)
		{
			while (*s && *s == quote)
				s++;
			while (*s && *s != quote)
			{
				s++;
				len++;
			}
			if (*s == quote)
				break ;
		}
		else
		{
			s++;
			len++;
		}
	}
	return (len);
}

int		find_close_quote(char **s, char quote, int *args)
{
	while (**s && **s == quote)
		(*s)++;
	while (**s && **s != quote)
		(*s)++;
	(*args)++;
	return (1);
}

int		arguments_counter(char *s)
{
	int args;
	int flag;

	args = 0;
	flag = 0;
	skip(&s, ' ');
	while (*s)
	{
		if (*s == '\'')
			flag = find_close_quote(&s, '\'', &args);
		else if (*s == '\"')
			flag = find_close_quote(&s, '\"', &args);
		//if ((*s == '\'' || *s == '\"') && *(s + 1) != ' ')
		//	args++;
		while (*s && *s != ' ')
			s++;
		if (!flag)
			args++;
		skip(&s, ' ');
		flag = 0;
	}
	return (args);
}

char	quote_type(char *arg)
{
	if (*arg == '\"')
		return ('\"');
	else if (*arg == '\'')
		return ('\'');
	else
		return ('\0');
}
