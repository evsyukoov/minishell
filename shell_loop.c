/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:20:27 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/13 18:24:41 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		launch(char **argv, char *envp[])
{
	pid_t child;
	int  status;
	(void)envp;
	child = fork();
	if (child < 0)
		perror("minishell");
	else if (child == 0)
	{
		if (execvp(argv[0], argv) == -1) {
			perror("command not found");
			return (1);
		}
	} else
	{
		waitpid(child, &status, WUNTRACED);
		while (WIFEXITED(status) == 0)
			waitpid(child, &status, WUNTRACED);
	}
	return (1);
}

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

int    execution(char **argv, char *envp[])
{
	char wd[256];

	if (ft_strcmp(argv[0], "cd") == 0)
		return (cd(argv));
	else if(ft_strcmp(argv[0], "pwd") == 0) {
		ft_putendl_fd(getwd(wd), 1);
		return (1);
	}
	else if (ft_strcmp(argv[0], "exit") == 0)
		exit(0);
	return (launch(argv, envp));
}

t_args *get_argv()
{
    char *line;
    t_args *lst;

    if (get_next_line(0, &line) < 0)
        return 0;
    if (*line == '\0')
    	return (0);
    //lst = create_list(line);
    //print_arg_list(lst);
   	lst = shell_split(line, ';', '|');
	print_arg_list(lst);
    return (lst);
}

void    shell_loop(char *envp[])
{
	int status;
    t_args *args_lst;

    status = 1;
    while (1)
   	{
		//for(int i = 0; envp[i]; i++)
		//	printf("%s\n", envp[i]);
		write(1, "minishell : ", 12);
		args_lst = get_argv();
		/*if (args_lst)
			status = execution(argv, envp);
		if (!status)
			break ;*/
		//free_arguments(&argv);
   }
}
