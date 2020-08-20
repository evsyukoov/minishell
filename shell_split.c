/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:08:59 by ccarl             #+#    #+#             */
/*   Updated: 2020/08/19 23:09:46 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		skip(char **s, char del)
{
	while (**s == del && **s)
		(*s)++;
}

static int		argument_len(char *s, char quote)
{
	int len;

	len = 0;
	while (*s && *s != ' ')
	{
		if (*s == quote)
		{
			while(*s && *s == quote)
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

static int     find_close_quote(char **s, char quote, int *args)
{
	while (**s && **s == quote)
		(*s)++;
	while (**s && **s != quote)
		(*s)++;
	(*args)++;
	return (1);
}

static int		arguments_counter(char *s)
{
	int args;
	int flag;
	int char_type;

	args = 0;
	flag = 0;
	skip(&s, ' ');
	while (*s)
	{
		char_type = 0;
		if (*s == '\'' && ++char_type)
			flag = find_close_quote(&s, '\'', &args);
		else if (*s == '\"')
			flag = find_close_quote(&s, '\"', &args);
		if ((*s == '\'' || *s == '\"') && *(s + 1) != ' ')
			args++;
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
		return('\'');
	else
		return ('\0');
}

void 	skip_env(char **arg)
{
	while (**arg && **arg != ' ')
		(*arg)++;
	skip(arg, ' ');
}

int 	env_len2(char *arg)
{
	int i;

	i = 0;
	while (arg[i] && arg[i] != ' ' && arg[i] != '\'' && arg[i] != '\"') {
		i++;
	}
	return (i);
}

char	*init_env_name(char *arg)
{
	char	*name;
	int		i;

	name = (char*)malloc(sizeof(char) * (env_len2(arg) + 1));
	arg += 1;
	i = 0;
	while (*arg && *arg != ' ' && *arg != '\"' && *arg != '$' && *arg != '\'')
		name[i++] = *arg++;
	name[i] = '\0';
	return (name);
}

char 	*get_begin_string(char *current_ptr, int len)
{
	int i;
	char *res;

	i = 0;
	current_ptr -= len;
	if (!(res = malloc(len + 1)))
		return (0);
	while (i < len)
		res[i++] = *current_ptr++;
	res[i] = '\0';
	return (res);
}

char 	*get_environment_string(char *arg, char **env, int begin_len)
{
	char *env_name;
	char *env_var;
	char *res;
	char *begin;

	begin = NULL;
	env_name = init_env_name(arg);
	env_var = get_env_var(env_name, env);
	if (!env_var)
		res = ft_strdup("\0");
	else
		res = get_env_var(env_name, env);
	begin = get_begin_string(arg, begin_len);
	if (begin)
		res = ft_strjoin(begin, res);
	free(begin);
	free(env_name);
	return (res);
}

int 	quotes_size(char *arg)
{
	int len;

	len = 0;
	while (arg[len] && arg[len] != '\"')
		len++;
	return (len);
}

char 	*join_char(char *arg, char c)
{
	char *res;
	int i;

	i = 0;
	if (!(res = (char*)malloc(ft_strlen(arg) + 2)))
		return (0);
	while (*arg)
		res[i++] = *arg++;
	res[i++] = c;
	res[i] = '\0';
	return (res);
}

char 	*get_environment_with_quotes(char *arg, char **env, int begin_len)
{
	char *res;
	char *tmp;

	res = get_environment_string(arg, env, begin_len);
	arg += env_len2(arg);
	while (*arg && *arg != '\"')
	{
		tmp = res;
		if (*arg != '$')
			res = join_char(res, *arg);
		else
		{
			res = ft_strjoin(res, get_environment_string(arg, env, 0));
			arg += env_len2(arg);
			if (*arg == '\'')
				res = join_char(res, *arg);
		}
		free(tmp);
		arg++;
	}
	return (res);
}

char 	*analize_env(char **arg, char **env)
{
	int i;
	char *res;
	int flag;
	int len;

	i = 0;
	flag = 0;
	len = 0;

	//баги - $HOME$PWD, $HOME>f, "$HOME">f
	res = NULL;
	//  '$HOME' - оставляем все как было
	if ((*arg)[i] == '\'')
		return (0);
	// "$HOME" ----> env_var
	if ((*arg)[i] == '\"' && --len)
		flag = 1;
	while ((*arg)[i] && (*arg)[i] != ' ') {
		if ((*arg)[i] == '$')
		{
			if (!flag)
			{
				res = get_environment_string(*arg + i, env, len);
				(*arg) += i + env_len2(*arg + i);
			}
			else
				{
				res = get_environment_with_quotes(*arg + i, env, len);
				(*arg) += i + quotes_size(*arg + i);
			}
			break ;
		}
		i++;
		len++;
	}
	return (res);
}

char 	*analize_exception(char *arg)
{
	char *res;

	res = NULL;
	//printf("arg = %s\n", arg);
	//printf("last code = %d\n", last_code);
	if (*arg == '$' && *(arg + 1) == '?') {
		printf("yes");
		res = ft_itoa(last_code);
	}
	//printf("res = %s\n", res);
	return (res);
}

char	**shell_split(char *arg, char **env)
{
	t_split var;
	char **res;
	char *tmp;

	var.args = arguments_counter(arg);
	//printf("args = %d", var.args);
	var.i = 0;
	if (!(res = (char**)malloc(sizeof(char*) * (var.args + 1))))
		return (0);
	skip(&arg, ' ');
	while (var.i < var.args)
	{
			if (*arg == '$' && *(arg + 1) == '?') {
				res[var.i] = ft_itoa(last_code);
				arg += 2;
				skip(&arg, ' ');
			}
			else if((tmp = analize_env(&arg, env)))
			{
				res[var.i] = tmp;
				skip_env(&arg);
			}
			else if (*arg == '~' && ++arg) {
				res[var.i] = ft_strdup(get_env_var("HOME", env));
				skip(&arg, ' ');
			}
			else {
				var.q_type = quote_type(arg);
				var.arg_len = argument_len(arg, var.q_type);
				res[var.i] = (char *) malloc(var.arg_len + 1);
				var.j = 0;
				skip(&arg, var.q_type);
				while (var.j < var.arg_len && *arg)
					res[var.i][var.j++] = *arg++;
				res[var.i][var.j] = '\0';

				skip(&arg, var.q_type);
				skip(&arg, ' ');
			}
		var.i++;
	}
	res[var.i] = NULL;
	return (res);
}

int 	number_of_arguments(char **argv)
{
	int j;

	j = 0;
	while (argv[j])
		j++;
	return (j);
}

void 	split_pipes(t_args **lst, char *arg_pipe, char **env)
{
	int j;
	char **argv_pipes;
	int num_of_args;

	j = 0;
	argv_pipes = ft_split(arg_pipe, '|');
	num_of_args = number_of_arguments(argv_pipes);
	while (argv_pipes[j])
	{
		{
			if (j < num_of_args - 1)
				push(lst, create_new_node(shell_split(argv_pipes[j], env), PIPE, NULL, NONE));
			else
				push(lst, create_new_node(shell_split(argv_pipes[j], env), COMMAND, NULL, NONE));
			j++;
		}
	}
	free_arguments(&argv_pipes);
}

t_args 	*create_list(char *arg, char **env)
{
	t_args *lst;
	char **argv1;
	int i;

	i = 0;
	lst = NULL;
	argv1 = ft_split(arg, ';');
	while(argv1[i])
	{
		if (ft_strchr(argv1[i], '|'))
			split_pipes(&lst, argv1[i], env);
		else
			push(&lst, create_new_node(shell_split(argv1[i], env), COMMAND, NULL, NONE));
		i++;
	}
	free_arguments(&argv1);
	//return (parse_redirections(lst));
	return lst;
}

char 	**case1(char **argv, int arg_index)
{
	int i;
	char **res;

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

char 	**case2(char **argv, int arg_index, size_t len)
{
	int i;
	char **res;
	int j;

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


int 	last_arg_len(char *arg, char redirection_type)
{
	int len;

	len = 0;
	while (*arg == redirection_type)
		arg++;
	while (arg[len] != redirection_type)
		len++;
	return (len);
}

char 	*find_file_name(char *arg)
{
	char *name;

	while (*arg)
	{
		if (*arg == '>')
		{
			if (*(arg + 1) == '>')
				arg += 2;
			else if (*(arg + 1) != '>')
				arg += 1;
			break;
		}
		arg++;
	}
	skip(&arg, '\'');
	skip(&arg, '\"');
	name = ft_strdup(arg);
	return (name);
}


//arg - та строчка, где встретился редирект
//argv - все строчки в ноде
//arg_index - индекс строки где встретился >

t_args 	*analize_redirection(char **argv, char *arg, int arg_index, t_args *old_node)
{
	t_args *node;

	node = NULL;
	// command > file
	if (ft_strlen(arg) == 1 && *arg == '>')
		node = create_new_node(case1(argv, arg_index), old_node->flag, argv[arg_index + 1], REWRITE);
	//command < file
	else if (ft_strlen(arg) == 1 && *arg == '<')
		node = create_new_node(case1(argv, arg_index), old_node->flag, argv[arg_index + 1], REVERSE);
	//command< file
	else if (str_endswith(arg, "<"))
		node = create_new_node(case2(argv, arg_index, ft_strlen(argv[arg_index]) - 1), old_node->flag, argv[arg_index + 1], REVERSE);
	//command<file or <file
	else if (ft_strchr(arg, '<'))
		node = create_new_node(case2(argv, arg_index, last_arg_len(arg, '<')), old_node->flag, ft_strdup(ft_strchr(arg,'<') + 1), REVERSE);
	//command >> file
	else if (ft_strlen(arg) == 2 && str_endswith(arg, ">"))
		node = create_new_node(case1(argv, arg_index), old_node->flag, argv[arg_index + 1], WRITE);
	//command> file
	else if (str_endswith(arg, ">") && arg[ft_strlen(arg) - 2] != '>')
		node = create_new_node(case2(argv, arg_index, ft_strlen(argv[arg_index]) - 1), old_node->flag,
							   argv[arg_index + 1], REWRITE);
	//command>> file
	else if (arg[ft_strlen(arg) - 1] == '>' && arg[ft_strlen(arg) - 2] == '>' && arg[ft_strlen(arg) - 3] != '>')
		node = create_new_node(case2(argv, arg_index, ft_strlen(argv[arg_index]) - 2), old_node->flag,
							   argv[arg_index + 1], WRITE);
	//command >file
	else if (str_startswith(arg, ">") && *(arg + 1) != '>')
		node = create_new_node(case1(argv, arg_index), old_node->flag, arg + 1, REWRITE);
	//command >>file
	else if (str_startswith(arg, ">") && *(arg + 1) == '>')
		node = create_new_node(case1(argv, arg_index), old_node->flag, arg + 2, WRITE);
	//command>file
	else if (*(ft_strchr(arg, '>') + 1) != '>' && *(ft_strchr(arg, '>') - 1) != '>')
		node = create_new_node(case2(argv, arg_index, last_arg_len(arg, '>')), old_node->flag, find_file_name(arg),
							   REWRITE);
	//command>>file
	else
		node = create_new_node(case2(argv, arg_index, last_arg_len(arg, '>')), old_node->flag, find_file_name(arg),
							   WRITE);
	//free_arguments(&argv);
	return (node);
}

int 	check_error_redirections(char **argv)
{
	int i;
	int j;
	int count1;

	i = 0;
	while (argv[i])
	{
		j = 0;
		count1 = 0;

		if (argv[i + 1] && !ft_strcmp(argv[i], ">") &&
		(!ft_strcmp(argv[i + 1], ">") || !ft_strcmp(argv[i + 1], ">>")))
			return (1);
		while (argv[i][j])
		{
			if (argv[i][j] == '>' || argv[i][j] == '<')
				count1++;
			if (count1 > 2)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/*void 	free_lst(t_args **lst)
{
	int i;

	i = 0;
	while (*lst)
	{
		while ((*lst)->args)
	}
}*/

t_args 	*parse_redirections(t_args *lst)
{
	int i;
	char **argv;
	t_args *new_node;	//new_node - нода в которой будет хранится инфа об имени файла и типе перенаправления
	t_args *head;
	int flag;

	head = NULL;
	while(lst)
	{
		argv = (lst->args);
		//print_argv(argv);
		i = 0;
		flag = 0;
		if (check_error_redirections(argv))
		{
			print_error_log("lsh: ", NULL, NULL, "syntax error near unexpected token '>'");
			last_code = 258;
			return (NULL);
		}
		while (argv[i])
		{
			if (ft_strchr(argv[i], '>') || ft_strchr(argv[i], '<'))
			{
				flag = 1;
				new_node = analize_redirection(argv, argv[i], i, lst);
				push(&head, new_node);
				free_arguments(&argv);
				break ;
			}
			i++;
		}
		if (!flag)
			push(&head, create_new_node(lst->args, lst->flag, lst->file_path, lst->file_option));
		lst = lst->next;
		//разобраться с утечками тут пизда по-видимости
		//free_arguments(&argv);
	}
	return (head);
}

