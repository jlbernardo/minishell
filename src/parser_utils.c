/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 20:24:28 by julberna          #+#    #+#             */
/*   Updated: 2024/01/30 17:46:50 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	set_pl(t_ast_node **pl, t_ast_node **parent, t_token **tokens)
{
	int	len;
	int	is_pipe;

	if (*tokens == NULL)
		return ;
	len = ft_strlen((*tokens)->literal);
	is_pipe = ft_strncmp((*tokens)->literal, "|", len);
	*pl = ft_calloc(1, sizeof(t_ast_node));
	if (pl == NULL)
		return ;
	(*pl)->type = PIPELINE;
	(*pl)->parent = *parent;
	if ((*pl)->parent == NULL && !is_pipe)
	{
		ft_printf("Syntax error near token %s\n", (*tokens)->literal);
		free(*pl);
		*pl = NULL;
	}
}

int	has_other_pipes(t_token *tokens)
{
	tokens = tokens->next;
	if (tokens == NULL)
		return (0);
	while (tokens != NULL)
	{
		if (!ft_strncmp(tokens->literal, "|", 1))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

void	set_cmd(t_ast_node **cmd_node, t_ast_node **parent)
{
	*cmd_node = ft_calloc(1, sizeof(t_ast_node));
	if (cmd_node == NULL)
		return ;
	(*cmd_node)->type = CMD;
	(*cmd_node)->parent = *parent;
	(*cmd_node)->left = NULL;
	(*cmd_node)->right = NULL;
	(*cmd_node)->data = malloc(sizeof(t_cmd));
	if ((*cmd_node)->data == NULL)
		return ;
	(*cmd_node)->data->pathname = ft_calloc(1, sizeof(char *));
	(*cmd_node)->data->redirects = ft_calloc(1, sizeof(t_redirect *));
	(*cmd_node)->data->word_list = ft_calloc(1, sizeof(t_wl_element *));
}

t_redirect	*new_redirect(t_token *tokens)
{
	t_redirect	*redir;

	redir = ft_calloc(1, sizeof(t_redirect));
	if (redir == NULL)
		return (NULL);
	if (ft_strncmp(tokens->literal, ">", 1) == 0)
		redir->type = REDOUT;
	else if (ft_strncmp(tokens->literal, ">>", 2) == 0)
		redir->type = APPEND;
	else if (ft_strncmp(tokens->literal, "<", 1) == 0)
		redir->type = REDIN;
	else if (ft_strncmp(tokens->literal, "<<", 2) == 0)
		redir->type = HEREDOC;
	redir->filename = ft_strdup(tokens->next->literal);
	redir->next = NULL;
	return (redir);
}
