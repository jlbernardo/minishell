#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <readline/readline.h>

typedef struct s_word
{
	char *word;
	int	flags;
} t_word;

typedef struct s_word_list
{
	t_word word;
	t_word *next;
} t_word_list;

#endif //MINISHELL_H
