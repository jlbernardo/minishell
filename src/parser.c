/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:55:58 by iusantos          #+#    #+#             */
/*   Updated: 2024/01/18 16:02:46 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_ast_node *parse_pipeline(t_token **tokens, t_ast_node *parent)
{
	t_ast_node *pl_node;

	if ((*tokens)->next == NULL)
		return (NULL);
	pl_node = malloc(sizeof(t_ast_node *));
	if (pl_node == NULL)
		return NULL;
	pl_node->type = PIPELINE;
	pl_node->parent = parent;
	pl_node->left = parse_cmd(tokens, pl_node);
	if ((*tokens)->next == NULL)
		pl_node->right = NULL;
	if (ft_strncmp((*tokens)->literal, "|", 1) == 0)
		pl_node->right = parse_pipeline(tokens, pl_node);
	else
		pl_node->right = parse_cmd(tokens, pl_node);

	return pl_node;
}

t_ast_node	*parse_cmd(t_token **tokens, t_ast_node *parent)
{
	t_ast_node	*cmd_node;

	cmd_node = malloc(sizeof(t_ast_node *));
	if (cmd_node == NULL)
		return NULL;
	cmd_node->type = CMD;
	cmd_node->parent = parent;
	cmd_node->left = NULL;
	cmd_node->right = NULL;
	set_cmd(cmd_node);
	while ((*tokens)->next != NULL
		&& ft_strncmp((*tokens)->literal, "|", 1) != 0)
	{
		if ((*tokens)->type == OPERAND && (*tokens)->next->type == WORD)
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
			ft_printf("Syntax error!");
			return NULL;
		}
	}
	return (cmd_node);
}

t_redirect	*new_redirect(t_token *tokens)
{
	t_redirect *redir;

	redir = malloc(sizeof(t_redirect *));
	if (redir == NULL)
		return (NULL);
	if (ft_strncmp(tokens->literal, ">", 1) == 0)
	{
		redir->type = REDOUT;
		redir->filename = ft_strdup(tokens->next->literal);
	}
	else if (ft_strncmp(tokens->literal, ">>", 2) == 0)
	{
		redir->type = APPEND;
		redir->filename = ft_strdup(tokens->next->literal);
	}
	else if (ft_strncmp(tokens->literal, "<", 1) == 0)
	{
		redir->type = REDIN;
		redir->filename = ft_strdup(tokens->next->literal);
	}
	else if (ft_strncmp(tokens->literal, "<<", 2) == 0)
	{
		redir->type = HEREDOC;
		redir->filename = ft_strdup(tokens->next->literal); //talvez heredoc nao seja aqui
	}
	redir->next = NULL;
	return (redir);
}

void	append_redirect(t_redirect *r, t_redirect **rl)
{
	if (*rl == NULL)
	{
		*rl = r;
		return ;
	}
	while ((*rl)->next != NULL)
		*rl = (*rl)->next;
	(*rl)->next = r;
	return ;
}

void	set_cmd(t_ast_node *cmd_node)
{
	cmd_node->data = malloc(sizeof(t_cmd *));
	if (cmd_node->data == NULL)
		return ;
	cmd_node->data->pathname = ft_calloc(sizeof(char *), 1);
	cmd_node->data->redirects = ft_calloc(sizeof(t_redirect **), 1);
	cmd_node->data->word_list = ft_calloc(sizeof(t_wl_element **), 1);
}

t_wl_element	*new_wle(char *s)
{
	t_wl_element	*wle;

	wle = malloc(sizeof(t_wl_element *));
	if (wle == NULL)
		return NULL;
	wle->word = ft_strdup(s);
	wle->next = NULL;
	return (wle);
}

void	append_wle(t_wl_element *w, t_wl_element **wl)
{
	if (*wl == NULL)
	{
		*wl = w;
		return ;
	}
	while ((*wl)->next != NULL)
		*wl = (*wl)->next;
	(*wl)->next = w;
	return ;
}
