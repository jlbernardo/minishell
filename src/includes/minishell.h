/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:44:05 by julberna          #+#    #+#             */
/*   Updated: 2024/02/01 18:08:45 by iusantos         ###   ########.fr       */
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

# define WORD 10
# define REDIRECT 11

# define REDOUT 20
# define APPEND 21
# define REDIN 22
# define HEREDOC 23

# define CMD 30
# define PIPELINE 31

# define HT_SIZE 1024

typedef struct s_ht_entry
{
	char				*name;
	char				*value;
	struct s_ht_entry	*next;
}	t_ht_entry;

typedef struct s_token
{
	int				type;
	char			*literal;
	struct s_token	*next;
}				t_token;

typedef struct s_ast_node
{
	int					type;
	struct s_ast_node	*parent;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	struct s_cmd		*data;
}				t_ast_node;

typedef struct s_cmd
{
	char				*pathname;
	struct s_wl_element	**word_list;
	struct s_redirect	**redirects;
}				t_cmd;

typedef struct s_redirect
{
	int					type;
	char				*filename;
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_wl_element
{
	char				*word;
	struct s_wl_element	*next;
}				t_wl_element;

typedef struct s_lexer
{
	char			*input;
	char			ch;
	unsigned int	pos;
	unsigned int	size;
	unsigned int	success;
	unsigned int	read_pos;
}				t_lexer;

/* MAIN CALLS */
int				lexer(t_token **tokens, t_ast_node **ast);
void			parser(t_token *tokens, t_ast_node **ast);
void			finisher(t_token *tokens, t_ast_node *ast);

/* LEXER */
int				is_operand(char ch);
char			*read_unquoted(t_lexer *l);
char			*read_quoted(t_lexer *l, char quote, int s_open, int d_open);
void			read_char(t_lexer *lex);
void			set_lexer(t_lexer *lex, char *input);
void			find_token(t_lexer *lex, t_token **tokens, int size);

/* VARIABLE EXPANDER */
void			expand_variables(t_token **tokens);
int				valid_variable(char *literal);
int				has_variable(char *literal);

/* PARSER */
int				has_other_pipes(t_token *tokens);
void			append_wle(t_wl_element *w, t_wl_element **wl);
void			append_redirect(t_redirect *r, t_redirect **rl);
void			set_cmd(t_ast_node **cmd_node, t_ast_node **parent);
void			set_pl(t_ast_node **pl, t_ast_node **parent, t_token **tokens);
t_ast_node		*parse_pipeline(t_token **tokens, t_ast_node *parent);
t_ast_node		*parse_cmd(t_token **tokens, t_ast_node *parent);
t_redirect		*new_redirect(t_token *tokens);
t_wl_element	*new_wle(char *s);

/* LIST HANDLER */
void			new_token(t_token **tk, int type, char *literal);
t_token			*tk_last(t_token *tk);

/* HASH TABLE */
unsigned int	hash(char *name);

/* FINISHER */
void			free_data(t_cmd	*cmd);
void			free_ast(t_ast_node *ast);
void			finish_lexer(t_lexer *lex);
void			free_wl2(t_wl_element **wl);
void			free_tokens(t_token *tokens);
void			free_redirects2(t_redirect **rl);
// void			free_wl(t_wl_element **wl);
// void			free_redirects(t_redirect **rl);

#endif
