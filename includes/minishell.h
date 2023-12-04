#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <readline/readline.h>

typedef enum e_tk_type
{
	SEMICOLON,
	LPAREN,
	RPAREN,
	PIPE,
	IDENT,
	BUILTIN,
	REDIN, //redirect input
	REDOUT, //redirect output
	HEREDOC,
	TILDE,
	STRING
} t_tk_type;

typedef struct s_tk
{
	t_tk_type	type;
	char		*literal;
	struct s_tk	*next;
} t_tk;

typedef struct s_lexer
{
	char	*input;
	unsigned int	pos;
	unsigned int	read_pos;
	char			ch;
	unsigned int	size;
} t_lexer;

#endif //MINISHELL_H
