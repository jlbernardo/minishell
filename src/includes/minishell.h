/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:44:05 by julberna          #+#    #+#             */
/*   Updated: 2024/01/17 17:54:00 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft/libft.h"
# include <stdio.h>
# include <stddef.h>
# include <readline/readline.h>

typedef enum e_tk_type
{
	WORD,
	OPERAND,
}				t_tk_type;

typedef struct s_token
{
	int				type;
	char			*literal;
	struct s_token	*next;
}				t_token;

typedef struct s_redirect
{
	int	mode;
	char	*filename;
	struct	s_redirect *next;
} t_redirect;

typedef struct s_cmd
{
	char			*pathname;
	char			**word_list;
	t_redirect		*redirects;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_pipeline
{
	t_cmd	*left;
	union u_pl_right
	{
		t_cmd *cmd;
		struct s_pipeline *pipeline;
	} *right;
} t_pipeline;

typedef struct s_wordlist
{
	char *word;
	struct s_wordlist *next;
} t_wordlist;

typedef struct s_lexer
{
	char			*input;
	char			ch;
	unsigned int	pos;
	unsigned int	size;
	unsigned int	read_pos;
}				t_lexer;

/* MAIN CALLS */
void	lexer(t_token **head);	

/* LEXER */
void	read_char(t_lexer *lex);
void	set_lexer(t_lexer *lex, char *input);
void	find_token(t_lexer *lex, t_token **tokens, int size);
int		is_operand(char ch);
char	*read_quoted(t_lexer *l);
char	*read_unquoted(t_lexer *l);

/* LIST HANDLER */
void	new_token(t_token **tk, int type, char *literal);
void	new_cmd(t_cmd **cmd, char *cmd_str, char *flag, char *args);
t_cmd	*cmd_last(t_cmd *cmd);
t_token	*tk_last(t_token *tk);

#endif
