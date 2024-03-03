/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:55:09 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/03/03 16:58:54 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ast	*create_pl_node(t_token **tokens, t_ast *parent, t_meta *meta)
{
	t_ast	*pl_node;

	set_pl(&pl_node, &parent, tokens, meta);
	if (!pl_node)
		return (NULL);
	pl_node->left = parse_cmd(tokens, pl_node, meta);
	if (!pl_node->success && parent)
		parent->success = LIE;
	return (pl_node);
}

t_ast	*handle_pipeline(t_token **tokens, t_ast *pl_node, t_meta *meta)
{
	if (!ft_strcmp((*tokens)->literal, "|") && has_other_pipes(*tokens)
		&& ft_strcmp((*tokens)->next->literal, "|"))
	{
		*tokens = (*tokens)->next;
		pl_node->right = parse_pipeline(tokens, pl_node, meta);
	}
	else if (!ft_strcmp((*tokens)->literal, "|")
		&& !has_other_pipes(*tokens) && (*tokens)->next != NULL)
	{
		*tokens = (*tokens)->next;
		pl_node->right = parse_cmd(tokens, pl_node, meta);
	}
	else
	{
		syntax_error((*tokens)->next, meta);
		pl_node->success = LIE;
	}
	return (pl_node);
}

t_ast	*parse_pipeline(t_token **tokens, t_ast *parent, t_meta *meta)
{
	t_ast	*pl_node;

	pl_node = create_pl_node(tokens, parent, meta);
	if (!pl_node || pl_node->left == NULL)
		return (pl_node);
	if (*tokens == NULL)
		return (pl_node);
	pl_node = handle_pipeline(tokens, pl_node, meta);
	return (pl_node);
}

t_ast	*parse_cmd(t_token **tokens, t_ast *parent, t_meta *meta)
{
	t_ast	*cmd_node;

	set_cmd(&cmd_node, &parent);
	while (*tokens != NULL && ft_strncmp((*tokens)->literal, "|", 1))
	{
		if ((*tokens)->type == REDIRECT
			&& (*tokens)->next && (*tokens)->next->type == WORD)
		{
			append_redirect(new_redirect(*tokens), &cmd_node->data->redirects);
			*tokens = (*tokens)->next->next;
		}
		else if ((*tokens)->type == WORD)
		{
			append_wle(new_wle((*tokens)->literal), &cmd_node->data->word_list);
			*tokens = (*tokens)->next;
		}
		else
		{
			syntax_error((*tokens)->next, meta);
			parent->success = LIE;
			free_cmd(cmd_node->data);
			free(cmd_node);
			return (NULL);
		}
	}
	return (cmd_node);
}
