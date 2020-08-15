/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 15:52:05 by mcaptain          #+#    #+#             */
/*   Updated: 2020/08/15 21:04:22 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_env(char *envp[])
{
	int i = 0;
	while(envp[i])
		printf("%s\n", envp[i++]);
}

int env_strcmp(char *name, char *env_var)
{
	int i;

	i = 0;
	while(name[i] == env_var[i])
		i++;
	if (name[i] == 0 && env_var[i] == '=')
		return(0);
	return(1);
}

char *get_env_var(char *name, char *envp[])
{
	int i;

	i = 0;
	while(envp[i])
	{
		if(!(env_strcmp(name, envp[i])))
			return (&envp[i][ft_strlen(name) + 1]);
		i++;
	}
	return (NULL);
}

int delete_env(int position, char *envp[])
{
	free(envp[position]);
	envp[position] = envp[position + 1];
	position++;
	while(envp[position])
	{
		envp[position] = envp[position + 1];
		position++;
	}
	return (0);
}

int unset(char *name, char *envp[])
{
	int i;

	i = 0;
	while(envp[i])
	{
		if(!(env_strcmp(name, envp[i])))
			return(delete_env(i, envp));
		i++;
	}
	return(1);
}


char *get_name(char *arg, char *envp[])
{
	int i;

	i = 0;

	if(!(ft_isdigit(arg[0])) && arg[0] != ' ')
	{
		while(arg[i] != '=')
		{
			if(arg[i] == ' ' || !arg[i])
				return (NULL);
			i++;

		}
		return(ft_substr(arg, 0, i));
	}
	return(NULL);
}

char *get_value(char *arg, char *envp[])
{

	if (!arg[0])
		return (NULL);
	if(arg[0] == '\'')
		return(ft_strtrim(arg, "\'"));
	if(arg[0] == '\"')
		return(ft_strtrim(arg, "\""));
	return (ft_strdup(arg));
}

int env_len(char *envp[])
{
	int i;

	i = 0;
	while(envp[i])
		i++;
	return (i);
}

char *joinenv(char *name, char *value)
{
	char	*res;
	int		i;
	int		j;
	
	j = 0;
	if (!name || !value)
		return (0);
	i = 0;
	res = (char*)malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(value) + 2));
	if (!res)
		return (0);
	while (name[j])
		res[i++] = name[j++];
	j = 0;
	res[i++] = '=';
	while (value[j])
		res[i++] = value[j++];
	free(value);
	free(name);
	res[i] = '\0';
	return (res);
}

//перемалочиваем список переменных увеличивая на один и вставляя переменную предпоследней

char **insert_env(char *name, char *value, char *envp[])
{
	int len;
	char **new_env;
	int i;

	i = 0;
	len = env_len(envp);
	if(!(new_env = malloc(sizeof(char *) * (len + 2))))
		return (NULL);
	new_env[len + 2] = 0;
	while(i < len + 1)
	{
		if (i == len)
		{
			new_env[i + 1] = envp[i];
			if (!(new_env[i] = joinenv(name, value)))
				return (NULL);
			break ;
		}
		new_env[i] = envp[i];
		i++;
	}
	return(new_env);
}

int rewrite_var(char *name, char *value, char *envp[])
{
	int i;
	char *buf;
	i = 0;
	while(envp[i])
	{
		if(!(env_strcmp(name, envp[i])))
		{
			buf = joinenv(name, value);
			if(!buf)
				return(0);
			free(envp[i]);
			envp[i] = buf;
			return(1);
		}
		i++;
	}
	return(0);
}

int export(char *arg, char **envp[])
{
	char *name;
	char *value;
	char **buf;
	
	if((name = get_name(arg, *envp)) && (value = get_value(&arg[ft_strlen(name) + 1], *envp)))
	{	
		if(rewrite_var(arg, value, *envp))
			return(0);
		if((buf = insert_env(name, value, *envp)))
		{
			envp = &buf;
			return (0);
		}
	}
	return (1);
}

char **realloc_env(char *envp[])
{
	int len;
	int len_word;
	char **new_env;
	char *buf;
	int i;

	len = env_len(envp);
	new_env = malloc(sizeof(char *) * (len + 1));
	i = 0;
	if(!new_env)
		return (NULL);		
	while(envp[i])
	{

		buf = malloc(ft_strlen(envp[i] + 1));
		if(!buf)
			return (NULL);
		ft_strlcpy(buf, envp[i], 1 + ft_strlen(envp[i]));
		new_env[i] = buf;
		i++;
	}
	new_env[i] = 0;
	return(new_env);
}

int main(int argc, char *argv[], char *envp[])
{
	char **new_envp;
	
	argc = 0;
	argv = 0;
	if(!(new_envp = realloc_env(envp)))
		return(0);
	export("en2=32", &new_envp);
    print_env(new_envp);
    return 0;
}