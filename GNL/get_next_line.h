/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 17:18:51 by denis             #+#    #+#             */
/*   Updated: 2020/08/27 21:57:27 by ccarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# define BUFFER_SIZE 100

int		get_next_line(int fd, char **line);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		find_pos(char *buff);
int		init_balance(char *buff, int pos, char **balance);
char	*check_balance(char **balance, char *line, int *flag);
char	*allocate_new(char *balance, int pos);
char	*init_line(char *s2);
char	*allocate_empty_line(char *line);

#endif
