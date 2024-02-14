/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:12:03 by julberna          #+#    #+#             */
/*   Updated: 2024/02/14 11:54:03 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	parser(t_token *tokens, t_ast **ast, t_hash **env_vars)
{
	expand_variables(&tokens, env_vars);
	remove_quotes(&tokens);
	*ast = parse_pipeline(&tokens, NULL);
	get_path(ast, env_vars);
	if ((*ast)->success == 1)
		return (1);
	else
		return (0);
}

t_ast	*parse_pipeline(t_token **tokens, t_ast *parent)
{
	t_ast	*pl_node;

	set_pl(&pl_node, &parent, tokens);
	if (!pl_node)
		return (NULL);
	pl_node->left = parse_cmd(tokens, pl_node);
	if (pl_node->left == NULL)
		return (pl_node);
	if (*tokens == NULL)
	{
		pl_node->success = 1;
		return (pl_node);
	}
	else if (!ft_strncmp((*tokens)->literal, "|", 1) && has_other_pipes(*tokens)
		&& ft_strncmp((*tokens)->next->literal, "|", 1))
	{
		*tokens = (*tokens)->next;
		pl_node->right = parse_pipeline(tokens, pl_node);
	}
	else if (!ft_strncmp((*tokens)->literal, "|", 1)
		&& !has_other_pipes(*tokens) && (*tokens)->next != NULL)
	{
		*tokens = (*tokens)->next;
		pl_node->right = parse_cmd(tokens, pl_node);
		if (pl_node->right == NULL)
		return (pl_node);
	}
	else
	{
		ft_printf("Syntax error near token %s\n", (*tokens)->literal);
		return (pl_node);
	}
	pl_node->success = 1;
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
			ft_printf("Syntax error near token %s\n", (*tokens)->literal);
			free_data(cmd_node->data);
			free(cmd_node);
			return (NULL);
		}
	}
	return (cmd_node);
}
