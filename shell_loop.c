/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:20:27 by ccarl             #+#    #+#             */
/*   Updated: 2020/07/21 21:07:12 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     cd(char **argv)
{
	if (chdir(argv[1]) != 0)
    	perror(argv[1]);
    return (1);
}

void	free_arguments(char ***argv)
{
	int i;

	i = 0;
	if (*argv) {
		while ((*argv)[i])
			free((*argv)[i++]);
		free(*argv);
	}
}

int    execution(char **argv)
{
	char wd[256];

	if (ft_strcmp(argv[0], "cd") == 0)
		cd(argv);
	else if(ft_strcmp(argv[0], "pwd") == 0)
		ft_putendl_fd(getwd(wd), 1);
	return (1);
}

char    **get_argv()
{
    char *line;
    char **argv;

    if (get_next_line(1, &line) < 0)
        return 0;
    if (*line == '\0')
    	return (0);
    argv = ft_split(line, ' ');
    free(line);
    return (argv);
}

void    shell_loop()
{
	int status;
    char **argv;

    status = 1;
    while (1)
   	{
       write(1, "minishell : ", 12);
       argv = get_argv();
       if (argv)
       		status = execution(argv);
       if (!status)
          break ;
       free_arguments(&argv);
   }
}

