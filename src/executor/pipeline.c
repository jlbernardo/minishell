/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:55:09 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/25 00:07:00 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ast	*create_pl_node(t_token **tokens, t_ast *parent)
{
	t_ast	*pl_node;

	set_pl(&pl_node, &parent, tokens);
	if (!pl_node)
		return (NULL);
	pl_node->left = parse_cmd(tokens, pl_node);
	return (pl_node);
}

t_ast	*handle_pipeline(t_token **tokens, t_ast *pl_node)
{
	if (!ft_strcmp((*tokens)->literal, "|") && has_other_pipes(*tokens)
		&& ft_strcmp((*tokens)->next->literal, "|"))
	{
		*tokens = (*tokens)->next;
		pl_node->right = parse_pipeline(tokens, pl_node);
	}
	else if (!ft_strcmp((*tokens)->literal, "|")
		&& !has_other_pipes(*tokens) && (*tokens)->next != NULL)
	{
		*tokens = (*tokens)->next;
		pl_node->right = parse_cmd(tokens, pl_node);
		if (pl_node->right == NULL)
			return (pl_node);
	}
	else
	{
		syntax_error((*tokens)->literal);
		return (pl_node);
	}
	return (pl_node);
}

t_ast	*parse_pipeline(t_token **tokens, t_ast *parent)
{
	t_ast	*pl_node;

	pl_node = create_pl_node(tokens, parent);
	if (!pl_node || pl_node->left == NULL)
		return (pl_node);
	if (*tokens == NULL)
	{
		pl_node->success = TRUTH;
		return (pl_node);
	}
	pl_node = handle_pipeline(tokens, pl_node);
	pl_node->success = TRUTH;
	return (pl_node);
}

t_ast	*parse_cmd(t_token **tokens, t_ast *parent)
{
	t_ast	*cmd_node;

	set_cmd(&cmd_node, &parent);
	while (*tokens != NULL && ft_strncmp((*tokens)->literal, "|", 1))
	{
		if ((*tokens)->type == REDIRECT && (*tokens)->next->type == WORD)
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
			syntax_error((*tokens)->literal);
			free_cmd(cmd_node->data);
			free(cmd_node);
			return (NULL);
		}
	}
	return (cmd_node);
}
