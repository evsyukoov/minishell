/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 15:43:47 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/17 16:27:36 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_fd(int fd)
{
	char buf[100];
	char *str;
	char *tmp;
	int status;
	
	str = strdup("");
	while((status = read(fd, buf, 100)) > 0)
	{
		tmp = str;
		buf[status] = 0;
		str = ft_strjoin(str, buf);
		free(tmp);
	}
	return (str);
}


char **rewrite_args(char **argv, char *new_arg)
{
		char **new_argv;
	char *buf;
	int i;
	new_argv = malloc(sizeof(char *) * (env_len(argv)+ 2));
	i = 0;
	if(!new_argv)
		return (NULL);		
	while(argv[i])
	{
		buf = malloc(ft_strlen(argv[i] + 1));
		if(!buf)
			return (NULL);
		ft_strlcpy(buf, argv[i], 1 + ft_strlen(argv[i]));
		new_argv[i] = buf;
		free(argv[i]);
		i++;
	}
	free(argv);
	new_argv[i] = new_arg;
	new_argv[i + 1] = 0;
	return(new_argv);
}

// void main()
// {
// 	char **argv;
// 	argv = malloc(sizeof(char *) * 4);
// 	argv[0] = ft_strdup("hi,");
// 	argv[1] = ft_strdup("you");
// 	argv[2] = ft_strdup("are");
// 	argv[3] = 0;
// 	argv = rewrite_args(argv, "dick");
// 	int i = 0;
// 	while(argv[i])
// 	{
// 		printf("%s ", argv[i++]);
// 	}
// }