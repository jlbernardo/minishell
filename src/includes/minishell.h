/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:44:05 by julberna          #+#    #+#             */
/*   Updated: 2024/01/18 11:06:44 by iusantos         ###   ########.fr       */
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

typedef struct s_wl_element
{
	char *word;
	struct s_wl_element *next;
} t_wl_element;

typedef struct s_cmd
{
	char			*pathname;
	t_wl_element	**word_list;
	t_redirect		*redirects;
}				t_cmd;

typedef union
{
	t_cmd	*cmd;
	struct s_pipeline	*pipeline;
}	u_plcmd;

typedef struct s_pipeline
{
	t_cmd	*left;
	u_plcmd	*right;
} t_pipeline;

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

/* PARSER */
u_plcmd *parse_pipeline(t_token *tokens);
t_cmd	*parse_cmd(t_token *tokens);
void	set_cmd(t_cmd *cmd);
t_wl_element	*new_wle(char *s);
void	append_wle(t_wl_element *w, t_wl_element **wl);

#endif
