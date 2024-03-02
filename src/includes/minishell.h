/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:44:05 by julberna          #+#    #+#             */
/*   Updated: 2024/03/02 17:55:29 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stddef.h>
# include <unistd.h>
# include <string.h>
# include <termios.h>
# include <sysexits.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <linux/limits.h>
# include <readline/history.h>
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

# define HT_SIZE 180

extern int	g_received_signal;

typedef struct s_meta
{
	struct s_token	*tokens;
	struct s_ast	*ast;
	struct s_hash	**hash;
	struct termios	*term;
	int				cmd_nbr;
}				t_meta;

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

typedef struct s_lexer
{
	char			*input;
	char			ch;
	unsigned int	pos;
	unsigned int	size;
	unsigned int	success;
	unsigned int	read_pos;
}				t_lexer;

typedef struct s_cmd
{
	char			*pathname;
	struct s_word	*word_list;
	struct s_redir	*redirects;
}				t_cmd;

typedef struct s_word
{
	char			*word;
	struct s_word	*next;
}				t_word;

typedef struct s_redir
{
	int				type;
	char			*filename;
	struct s_redir	*next;
}				t_redir;

typedef struct s_builtin
{
	char	*cmd_name;
	int		(*function)(t_meta *, t_word *);
}				t_builtin;

/* MAIN CALLS */
int				lexer(t_meta *meta);
int				parser(t_meta *meta);
void			executor(t_meta *meta);
void			set_meta(t_meta *meta, char **__environ);
void			finisher(t_meta meta, char *flag, int exit_code);

/* LEXER */
void			find_token(t_lexer *lex, t_token **tokens, int size);
void			replace_variable(char **input, t_hash **hash);
void			expand_variable(char **input, t_meta *meta);
void			set_lexer(t_lexer *lex, char *input);
void			read_char(t_lexer *lex);
char			*read_unquoted(t_lexer *lex);
char			*get_variable_name(char *literal);
char			*read_quoted(t_lexer *lex, char quote, int s_open, int d_open);

/* PARSER */
void			find_path(t_ast **ast, char **paths);
void			get_path(t_ast **ast, t_hash **hash);
void			remove_empty_tokens(t_token **tokens);
void			syntax_error(char *token, t_meta *meta);
void			set_cmd(t_ast **cmd_node, t_ast **parent);
void			remove_quotes(t_token **tokens, int i, int len, char quote);
void			set_pl(t_ast **pl, t_ast **parent, t_token **tk, t_meta *meta);
t_ast			*parse_pipeline(t_token **tokens, t_ast *parent, t_meta *meta);
t_ast			*parse_cmd(t_token **tokens, t_ast *parent, t_meta *meta);

/* EXECUTOR */
int				get_envp_size(t_hash **hash);
int				get_wl_size(t_word *word_list);
int				handle_exit_status(t_meta *meta);
int				run_builtin(t_meta *meta, t_word *wl);
void			run_pipeline(t_ast *ast, t_meta *meta);
void			format_envp(t_hash **hash, char ***array);
void			run_executable(t_cmd *data, t_meta *meta);
void			run_simple_command(t_ast *cmd, t_meta *meta);
void			format_argv(t_word *word_list, char ***array);
void			handle_null_pathname(char *cmd, t_meta *meta);
void			exec_forked_command(t_cmd *data, t_meta *meta);
void			upd_simple_exit_status(int exit_status, t_meta	*meta);
void			last_pipeline_cmd(t_ast *ast, int *pipe_fd, t_meta *meta);
void			middle_pipeline_cmd(t_ast *ast, int *pipe_fd, t_meta *meta);
void			first_pipeline_cmd(t_ast *ast, int pipe_fd[2], t_meta *meta);
void			path_error(t_meta *meta, char *path, char *msg, int exit_code);

/* HEREDOC EXECUTION */
int				execute_heredocs(t_ast *ast, t_meta *meta);
void			fill_tmpfile(int fd, t_redir *r, t_meta *meta);
void			capture_content(t_redir *rl, t_meta *meta);
void			child_heredoc(t_meta *meta, t_ast *ast);
void			write_and_close(int fd);
int				handle_eof(char *input, t_redir *r, int fd, t_meta *meta);
void			expand_and_write(char *input, int fd, t_meta *meta);
char			*gen_tmpfile_name(int cmd_nbr);

/* REDIRECTS */
int				process_redirects(t_redir *rl, t_meta *meta);
int				red_input(t_redir *r);
int				red_append(t_redir *r);
int				red_output(t_redir *r);
int				red_heredoc(t_redir *r, int cmd_nbr);
void			print_nsf_error_msg(char *filename);
void			print_np_error_msg(char *filename);

/* LIST HANDLERS */
void			sort_vars(t_word **vars, t_word *first, t_word *first_p);
void			append_redirect(t_redir *new_node, t_redir **redir_list);
void			new_token(t_token **tokens, int type, char *literal);
void			append_wle(t_word *new_node, t_word **word_list);
void			populate_sort_vars(t_hash **ht, t_word **vars);
t_word			*new_wle(char *string);
t_token			*tk_last(t_token *tokens);
t_redir			*new_redirect(t_token *tokens);

/* SIGNALS */
void			sig_deal(int signo);
void			eof_signal(t_meta *meta);
void			signal_handler(t_meta *meta);
void			mid_exec_signal(int child_pid);
void			heredoc_sigint_handler(int signum);

/* HASH TABLE */
int				last_exit(t_meta *meta);
char			*grab_value(char *name, t_hash **ht);
void			set_hashtable(char **env, t_hash **ht);
void			add_upd_hashtable(char *name, char *value, t_hash **ht);
t_hash			*create_kv_pair(char *name, char *value);
unsigned int	hash(char *name);

/* BUILTINS */
int				cd(t_meta *meta, t_word *wl);
int				pwd(t_meta *meta, t_word *wl);
int				env(t_meta *meta, t_word *wl);
int				echo(t_meta *meta, t_word *wl);
int				unset(t_meta *meta, t_word *wl);
int				export(t_meta *meta, t_word *wl);
int				ft_exit(t_meta *meta, t_word *wl);
void			print_export(t_word *vars, t_hash **ht);

/* CONDITIONALS */
int				is_operand(char ch);
int				sorted(t_word *vars);
int				is_builtin(char *cmd);
int				is_readonly(char *literal);
int				has_variable(char *literal);
int				valid_variable(char *literal);
int				has_other_pipes(t_token *tokens);
int				quote_open(int s_open, int d_open);

/* FINISHERS */
void			safe_free(void *p);
void			close_all_fds(void);
void			free_ast(t_ast *ast);
void			free_cmd(t_cmd	*cmd);
void			free_hash(t_hash **ht);
void			free_ht_entry(t_hash *ht);
void			finish_lexer(t_lexer *lex);
void			free_tokens(t_token *tokens);
void			free_wordlist(t_word *word_list);
void			free_redirects(t_redir *redir_list);
void			free_str_array(char **array, int size);

#endif
