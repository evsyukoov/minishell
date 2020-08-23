//
// Created by Casie Carl on 8/22/20.
//

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include <stdlib.h>
# include "../libft/libft.h"

typedef struct 		s_names
{
	char 			*name;
	int 			type;
	struct s_names  *next;
}					t_files;

t_files	*new_redirection(char *file_path, int file_option);

#endif //CUB_REDIRECTIONS_H
