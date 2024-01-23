/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:44:05 by julberna          #+#    #+#             */
/*   Updated: 2024/01/23 14:06:06 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft/libft.h"
# include <stdio.h>
# include <stddef.h>
# include <readline/readline.h>

# define WORD 10
# define OPERAND 11

# define REDOUT 20
# define APPEND 21
# define REDIN 22
# define HEREDOC 23

# define CMD 30
# define PIPELINE 31

typedef struct s_cmd
{
	char			*pathname;
	struct s_wl_element	**word_list;
	struct s_redirect	**redirects;
}				t_cmd;

typedef struct s_ast_node
{
	int type;
	struct s_ast_node *parent;
	struct s_ast_node *left;
	struct s_ast_node *right;
	struct s_cmd	*data;
}	t_ast_node;

typedef struct s_token
{
	int		type;
	char			*literal;
	struct s_token	*next;
}				t_token;

typedef struct s_redirect
{
	int	type;
	char	*filename;
	struct	s_redirect *next;
} t_redirect;

typedef struct s_wl_element
{
	char *word;
	struct s_wl_element *next;
} t_wl_element;

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
// t_cmd	*cmd_last(t_cmd *cmd);
t_token	*tk_last(t_token *tk);

/* PARSER */
t_ast_node *parse_pipeline(t_token **tokens, t_ast_node *parent);
int	has_other_pipes(t_token *tokens);
t_ast_node	*parse_cmd(t_token **tokens, t_ast_node *parent);
void	set_cmd(t_ast_node *cmd_node, t_ast_node *parent);
t_redirect	*new_redirect(t_token *tokens);
void	append_redirect(t_redirect *r, t_redirect **rl);
t_wl_element	*new_wle(char *s);
void	append_wle(t_wl_element *w, t_wl_element **wl);

void	free_wl(t_wl_element **wl);
void	free_wl2(t_wl_element **wl);

#endif
