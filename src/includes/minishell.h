/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:44:05 by julberna          #+#    #+#             */
/*   Updated: 2024/01/18 19:10:24 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft/libft.h"
# include <stdio.h>
# include <stddef.h>
# include <readline/readline.h>
# define LIE 0
# define TRUTH 1
# define WORD 0
# define REDIRECT 1

typedef struct s_token
{
	int				type;
	char			*literal;
	struct s_token	*next;
}				t_token;

typedef struct s_cmd
{
	t_list			*args;
	t_list			*redir;
}				t_cmd;

typedef struct s_pipeline
{
	void				*left;
	void				*right;
	struct s_pipeline	*next;
}				t_pipeline;

typedef struct s_lexer
{
	char			*input;
	char			ch;
	unsigned int	pos;
	unsigned int	size;
	unsigned int	read_pos;
}				t_lexer;

/* MAIN CALLS */
void		lexer(t_token **tokens);
void		parser(t_token **tokens);

/* LEXER */
void		read_char(t_lexer *lex);
void		set_lexer(t_lexer *lex, char *input);
void		find_token(t_lexer *lex, t_token **tokens, int size);
int			is_operand(char ch);
char		*read_quoted(t_lexer *l);
char		*read_unquoted(t_lexer *l);

/* PARSER */
void		check_operator(t_token **tokens, t_pipeline **head, int *is_cmd);
void		add_word_left(t_pipeline **head, t_token **tokens);

/* LIST HANDLER */
void		new_token(t_token **tk, int type, char *literal);
void		new_pipeline(t_pipeline **head, t_list **node);
t_token		*tk_last(t_token *tk);
t_pipeline	*pipeline_last(t_pipeline *head);

/* FINISHER */
void		finish_lexer(t_lexer *lex);

#endif
