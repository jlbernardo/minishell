#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <readline/readline.h>

typedef enum e_tk_type
{
	CMND,
	IDENT,
	DELIM
} t_tk_type;

typedef struct s_tk
{
	t_tk_type	type;
	char		*literal;
} t_tk;

#endif //MINISHELL_H
