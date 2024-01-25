/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:55:58 by iusantos          #+#    #+#             */
/*   Updated: 2024/01/25 13:30:12 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	*panic(char *token)
{
	ft_printf("Syntax error near %s", token);
	return (NULL);
}

t_ast_node	*parse_pipeline(t_token **tokens, t_ast_node *parent)
{
	t_ast_node	*pl_node;

	set_pl(&pl_node, &parent, tokens);
	if (!pl_node)
		return (NULL);
	pl_node->left = parse_cmd(tokens, pl_node);
	if (*tokens == NULL)
		pl_node->right = NULL;
	else if (!ft_strncmp((*tokens)->literal, "|", 1)
		&& has_other_pipes(*tokens)
		&& ft_strncmp((*tokens)->next->literal, "|", 1))
	{
		*tokens = (*tokens)->next;
		pl_node->right = parse_pipeline(tokens, pl_node);
	}
	else if (!ft_strncmp((*tokens)->literal, "|", 1)
		&& !has_other_pipes(*tokens) && (*tokens)->next->next != NULL)
	{
		*tokens = (*tokens)->next;
		pl_node->right = parse_cmd(tokens, pl_node);
	}
	else
		return (panic((*tokens)->literal));
	return (pl_node);
}

t_ast_node	*parse_cmd(t_token **tokens, t_ast_node *parent)
{
	t_ast_node	*cmd_node;

	cmd_node = ft_calloc(1, sizeof(t_ast_node));
	if (cmd_node == NULL)
		return (NULL);
	set_cmd(cmd_node, parent);
	while (*tokens && ft_strncmp((*tokens)->literal, "|", 1))
	{
		if ((*tokens)->type == REDIRECT && (*tokens)->next->type == WORD)
		{
			append_redirect(new_redirect(*tokens), cmd_node->data->redirects);
			*tokens = (*tokens)->next->next;
		}
		else if ((*tokens)->type == WORD)
		{
			append_wle(new_wle((*tokens)->literal), cmd_node->data->word_list);
			*tokens = (*tokens)->next;
		}
		else
		{
			ft_printf("Syntax error near %s", (*tokens)->literal);
			return (NULL);
		}
	}
	return (cmd_node);
}
