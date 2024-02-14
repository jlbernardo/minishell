/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:44:05 by julberna          #+#    #+#             */
/*   Updated: 2024/02/14 14:52:10 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft/libft.h"
# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <errno.h>
# include <linux/limits.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <sys/types.h>

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

# define HT_SIZE 10

typedef struct s_hash
{
	char			*name;
	char			*value;
	struct s_hash	*next;
}				t_hash;

typedef struct s_token
{
	int				type;
	char			*literal;
	struct s_token	*next;
}				t_token;

typedef struct s_ast
{
	int				type;
	int				success;
	struct s_ast	*parent;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_cmd	*data;
}				t_ast;

typedef struct s_cmd
{
	char			*pathname;
	struct s_word	*word_list;
	struct s_redir	*redirects;
}				t_cmd;

typedef struct s_redir
{
	int				type;
	char			*filename;
	struct s_redir	*next;
}				t_redir;

typedef struct s_word
{
	char			*word;
	struct s_word	*next;
}				t_word;

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
int				lexer(t_token **tokens, t_ast **ast);
int				parser(t_token *tokens, t_ast **ast, t_hash **env_vars);
void			executor(t_ast *ast);
void			finisher(t_token *tokens, t_ast *ast);

/* LEXER */
int				is_operand(char ch);
char			*read_unquoted(t_lexer *l);
char			*read_quoted(t_lexer *l, char quote, int s_open, int d_open);
void			find_token(t_lexer *lex, t_token **tokens, int size);
void			set_lexer(t_lexer *lex, char *input);
void			read_char(t_lexer *lex);

/* EXPANDER */
int				has_variable(char *literal);
int				valid_variable(char *literal);
char			*get_variable_name(char *literal);
void			replace_variable(t_token **tokens, t_hash **ht);
void			expand_variables(t_token **tokens, t_hash **ht);

/* PARSER */
int				not_builtin(char *cmd);
int				has_other_pipes(t_token *tokens);
void			remove_quotes(t_token **tokens);
void			append_wle(t_word *w, t_word **wl);
void			find_path(t_ast **ast, char **paths);
void			get_path(t_ast **ast, t_hash **env_vars);
void			append_redirect(t_redir *r, t_redir **rl);
void			set_cmd(t_ast **cmd_node, t_ast **parent);
void			set_pl(t_ast **pl, t_ast **parent, t_token **tokens);
t_ast			*parse_pipeline(t_token **tokens, t_ast *parent);
t_ast			*parse_cmd(t_token **tokens, t_ast *parent);
t_redir			*new_redirect(t_token *tokens);
t_word			*new_wle(char *s);

/* EXECUTOR */
void			run_simple_command(t_ast *cmd_node);
int				is_builtin(char *cmd_name);
void			run_builtin(t_word	*wl);
void			run_executable(t_cmd *data);
char			**stringfy(t_word *wl);
int				get_size(t_word *wl);

/* LIST HANDLER */
void			new_token(t_token **tk, int type, char *literal);
t_token			*tk_last(t_token *tk);

/* HASH TABLE */
char			*grab_value(char *name, t_hash **ht);
t_hash			*create_kv_pair(char *name, char *value);
void			add_or_upd_ht_entry(char *name, char *value, t_hash **ht);
void			add_env_to_ht(char **env, t_hash **ht);
void			free_ht_entry(t_hash *ht);
void			free_ht(t_hash **ht);
void			safe_free(void *p);
unsigned int	hash(char *name);

/* BUILTINS */
int				pwd(void);
int				env(t_hash **ht);
int				echo(t_token *tokens);

/* FINISHER */
void			free_ast(t_ast *ast);
void			free_data(t_cmd	*cmd);
void			free_wl2(t_word *wl);
void			finish_lexer(t_lexer *lex);
void			free_tokens(t_token *tokens);
void			free_redirects2(t_redir *rl);
// void			free_wl(t_word **wl);
// void			free_redirects(t_redir **rl);

#endif
