/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_structures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:13:03 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/03/05 17:17:56 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_meta(t_meta *meta, char **__environ)
{
	meta->term = ft_calloc(1, sizeof(struct termios));
	if (tcgetattr(STDIN_FILENO, meta->term) < 0)
	{
		perror("minishell: tcsetattr");
		exit (EXIT_FAILURE);
	}
	meta->hash = ft_calloc(HT_SIZE, sizeof(t_hash *));
	set_hashtable(__environ, meta->hash);
	add_upd_hashtable("?", "0", meta->hash);
	meta->cmd_nbr = 0;
}

void	set_lexer(t_lexer *lex, char *input)
{
	lex->input = input;
	lex->ch = 0;
	lex->pos = 0;
	lex->read_pos = 0;
	lex->success = TRUTH;
	lex->size = ft_strlen(input);
}

void	set_pl(t_ast **pl, t_ast **parent, t_token **tk, t_meta *meta)
{
	int	len;
	int	is_pipe;

	if (tk == NULL)
		return ;
	len = ft_strlen((*tk)->literal);
	is_pipe = ft_strncmp((*tk)->literal, "|", len);
	*pl = ft_calloc(1, sizeof(t_ast));
	if (pl == NULL)
		return ;
	(*pl)->type = PIPELINE;
	(*pl)->parent = *parent;
	(*pl)->success = TRUTH;
	if ((*pl)->parent == NULL && !is_pipe)
	{
		syntax_error(*tk, meta);
		free(*pl);
		*pl = NULL;
	}
}

void	set_cmd(t_ast **cmd_node, t_ast **parent)
{
	*cmd_node = ft_calloc(1, sizeof(t_ast));
	if (cmd_node == NULL)
		return ;
	(*cmd_node)->type = CMD;
	(*cmd_node)->parent = *parent;
	(*cmd_node)->left = NULL;
	(*cmd_node)->right = NULL;
	(*cmd_node)->data = malloc(sizeof(t_cmd));
	if ((*cmd_node)->data == NULL)
		return ;
	(*cmd_node)->data->pathname = NULL;
	(*cmd_node)->data->redirects = NULL;
	(*cmd_node)->data->word_list = NULL;
}

void	set_hashtable(char **env, t_hash **ht)
{
	char			*pair[2];
	unsigned int	len_after_equal;
	unsigned int	len_before_equal;

	while (*env)
	{
		len_before_equal = ft_strchr(*env, '=') - *env;
		len_after_equal = ft_strlen(*env) - len_before_equal - 1;
		pair[0] = ft_substr(*env, 0, len_before_equal);
		pair[1] = ft_substr(ft_strchr(*env, '='), 1, len_after_equal);
		add_upd_hashtable(pair[0], pair[1], ht);
		safe_free(pair[0]);
		safe_free(pair[1]);
		env++;
	}
}
