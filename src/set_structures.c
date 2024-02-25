/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_structures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:13:03 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/24 19:15:41 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	set_meta(t_meta *meta, char **__environ)
{
	meta->hash = ft_calloc(HT_SIZE, sizeof(t_hash *));
	add_env_to_ht(__environ, meta->hash);
	add_or_upd_ht_entry("?", "0", meta->hash);
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

void	set_pl(t_ast **pl, t_ast **parent, t_token **tokens)
{
	int	len;
	int	is_pipe;

	if (tokens == NULL)
		return ;
	len = ft_strlen((*tokens)->literal);
	is_pipe = ft_strncmp((*tokens)->literal, "|", len);
	*pl = ft_calloc(1, sizeof(t_ast));
	if (pl == NULL)
		return ;
	(*pl)->type = PIPELINE;
	(*pl)->parent = *parent;
	(*pl)->success = 0;
	if ((*pl)->parent == NULL && !is_pipe)
	{
		syntax_error((*tokens)->literal);
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
