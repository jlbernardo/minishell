/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 20:24:28 by julberna          #+#    #+#             */
/*   Updated: 2024/02/08 20:31:49 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	set_pl(t_ast **pl, t_ast **parent, t_token **tokens)
{
	int	len;
	int	is_pipe;

	if (*tokens == NULL)
		return ;
	len = ft_strlen((*tokens)->literal);
	is_pipe = ft_strncmp((*tokens)->literal, "|", len);
	*pl = ft_calloc(1, sizeof(t_ast));
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
	(*cmd_node)->data->redirects = NULL;
	(*cmd_node)->data->word_list = NULL;
}

t_redir	*new_redirect(t_token *tokens)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
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

void	remove_quotes(t_token **tokens)
{
	int		i;
	int		len;
	char	quote;

	i = 0;
	if (!*tokens)
		return ;
	while ((*tokens)->literal[i] != '\0')
	{
		if ((*tokens)->literal[i] == '"' || (*tokens)->literal[i] == '\'')
		{
			quote = (*tokens)->literal[i];
			len = ft_strlen((*tokens)->literal) - i;
			ft_memmove(&(*tokens)->literal[i], &(*tokens)->literal[i + 1], len);
			while ((*tokens)->literal[i] != quote)
				i++;
			len = ft_strlen((*tokens)->literal) - i;
			ft_memmove(&(*tokens)->literal[i], &(*tokens)->literal[i + 1], len);
		}
		i++;
	}
	remove_quotes(&(*tokens)->next);
}
