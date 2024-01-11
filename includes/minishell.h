/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:44:05 by julberna          #+#    #+#             */
/*   Updated: 2024/01/11 20:18:57 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>

typedef struct s_token
{
	char			*type;
	char			*literal;
	struct s_token	*next;
} t_token;

typedef struct s_cmd
{
	char	*cmd;
	char	*flag;
	char	**args;
	int		out_fd;
	int		out_mode;
	int		in_fd;
	int		in_delim;
	int		err_fd;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_lexer
{
	char			*input;
	unsigned int	pos;
	char			ch;
	unsigned int	read_pos;
	unsigned int	size;
} t_lexer;

// ** LEXER **
void	lexer(t_token **head);
void	read_char(t_lexer *lex);
void	set_lexer(t_lexer *lex, char *input);
void	*new_token(t_token **tk, char *type, char *literal);
char	*read_string(t_lexer *l);
#endif
