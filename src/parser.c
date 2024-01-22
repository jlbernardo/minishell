/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:55:58 by iusantos          #+#    #+#             */
/*   Updated: 2024/01/22 11:47:37 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//syntax error: pipe op followed by another pipe op
t_ast_node *parse_pipeline(t_token **tokens, t_ast_node *parent)
{
	t_ast_node *pl_node;

	pl_node = malloc(sizeof(t_ast_node));
	if (pl_node == NULL)
		return NULL;
	set_pl_node(pl_node);
	pl_node->type = PIPELINE;
	*(pl_node->parent) = parent;
	if (*(pl_node->parent) == NULL
		&& ft_strncmp((*tokens)->literal, "|", 1) == 0)
	{
		ft_printf("Syntax error near token %s\n", (*tokens)->literal);
		return NULL;
	}
	*(pl_node->left) = parse_cmd(tokens, pl_node);
	if ((*tokens)->next == NULL)
		*(pl_node->right) = NULL;
	if (ft_strncmp((*tokens)->literal, "|", 1) == 0
		&& has_other_pipes(*tokens) == 1
		&& ft_strncmp((*tokens)->next->literal, "|", 1) != 0)
	{
		*tokens = (*tokens)->next;
		*(pl_node->right) = parse_pipeline(tokens, pl_node);
	}
	else if (ft_strncmp((*tokens)->literal, "|", 1) == 0
		&& has_other_pipes(*tokens) == 0
		&& (*tokens)->next->next != NULL)
	{
		*tokens = (*tokens)->next;
		*(pl_node->right) = parse_cmd(tokens, pl_node);
	}
	else {
		ft_printf("syntax error near %s", (*tokens)->literal);
	}

	return pl_node;
}

void set_pl_node(t_ast_node *pl_node)
{
	pl_node->parent = ft_calloc(1, sizeof(t_ast_node *));
	pl_node->left = ft_calloc(1, sizeof(t_ast_node *));
	pl_node->right = ft_calloc(1, sizeof(t_ast_node *));
	pl_node->data = NULL;
}

int	has_other_pipes(t_token *tokens)
{
	tokens = tokens->next;
	while (tokens != NULL)
	{
		if (ft_strncmp(tokens->literal, "|", 1) == 0)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

//syntax error: redirect op not followed by WORD.
t_ast_node	*parse_cmd(t_token **tokens, t_ast_node *parent)
{
	t_ast_node	*cmd_node;

	cmd_node = malloc(sizeof(t_ast_node));
	if (cmd_node == NULL)
		return NULL;
	set_cmd(cmd_node);
	cmd_node->type = CMD;
	*(cmd_node->parent) = parent;
	cmd_node->left = NULL;
	cmd_node->right = NULL;
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
			ft_printf("Syntax error near %s", (*tokens)->literal);
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
	t_redirect	*og;

	og = *rl;
	if (*rl == NULL)
	{
		*rl = r;
		return ;
	}
	while ((*rl)->next != NULL)
		*rl = (*rl)->next;
	(*rl)->next = r;
	*rl = og;
	return ;
}

void	set_cmd(t_ast_node *cmd_node)
{
	cmd_node->parent = ft_calloc(1, sizeof(t_ast_node));
	cmd_node->data = malloc(sizeof(t_cmd));
	if (cmd_node->data == NULL)
		return ;
	cmd_node->data->pathname = ft_calloc(1, sizeof(char *));
	cmd_node->data->redirects = ft_calloc(1, sizeof(t_redirect *));
	cmd_node->data->word_list = ft_calloc(1, sizeof(t_wl_element *));
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
	t_wl_element *og;

	og = *wl;
	if (*wl == NULL)
	{
		*wl = w;
		return ;
	}
	while ((*wl)->next != NULL)
		*wl = (*wl)->next;
	(*wl)->next = w;
	*wl = og;
	return ;
}
