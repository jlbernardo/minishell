/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:48:46 by julberna          #+#    #+#             */
/*   Updated: 2024/02/25 19:11:19 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_token(t_token **tokens, int type, char *literal)
{
	t_token	*new_node;

	new_node = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_node)
		return ;
	new_node->type = type;
	new_node->literal = ft_strdup(literal);
	new_node->next = NULL;
	if (!*tokens)
		*tokens = new_node;
	else
		tk_last(*tokens)->next = new_node;
}

t_token	*tk_last(t_token *tokens)
{
	if (tokens == NULL)
		return (NULL);
	while (tokens->next != NULL)
		tokens = tokens->next;
	return (tokens);
}

t_word	*new_wle(char *string)
{
	t_word	*new_node;

	new_node = malloc(sizeof(t_word));
	if (new_node == NULL)
		return (NULL);
	new_node->word = ft_strdup(string);
	new_node->next = NULL;
	return (new_node);
}

void	append_wle(t_word *new_node, t_word **word_list)
{
	t_word	*temp;

	temp = *word_list;
	if (*word_list == NULL)
	{
		*word_list = new_node;
		return ;
	}
	while ((*word_list)->next != NULL)
		*word_list = (*word_list)->next;
	(*word_list)->next = new_node;
	*word_list = temp;
	return ;
}

void	append_redirect(t_redir *new_node, t_redir **redir_list)
{
	t_redir	*temp;

	temp = *redir_list;
	if (*redir_list == NULL)
	{
		*redir_list = new_node;
		return ;
	}
	while ((*redir_list)->next != NULL)
		*redir_list = (*redir_list)->next;
	(*redir_list)->next = new_node;
	*redir_list = temp;
	return ;
}
