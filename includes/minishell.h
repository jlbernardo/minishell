/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:44:05 by julberna          #+#    #+#             */
/*   Updated: 2024/01/10 14:54:12 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>

typedef enum e_tk_type
{
	END,
	ILLEGAL,
	SEMICOLON,
	LPAREN,
	RPAREN,
	PIPE,
	VAR,
	WORD,
	BUILTIN,
	FLAG,
	REDIN, //redirect input
	REDOUT, //redirect output
	APPEND,
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

// ** LEXER **
void	read_char(t_lexer *l);
void	set_lexer(t_lexer *lexer, char *input);
t_tk	*new_token(t_tk_type type, char *literal);

#endif //MINISHELL_H
