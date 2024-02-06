/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:48:46 by julberna          #+#    #+#             */
/*   Updated: 2024/02/06 15:13:59 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_token	*tk_last(t_token *tk);

void	new_token(t_token **tk, int type, char *literal)
{
	t_token	*new_node;

	new_node = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_node)
		return ;
	new_node->type = type;
	new_node->literal = ft_strdup(literal);
	new_node->next = NULL;
	if (!*tk)
		*tk = new_node;
	else
		tk_last(*tk)->next = new_node;
}

t_token	*tk_last(t_token *tk)
{
	if (tk == NULL)
		return (NULL);
	while (tk->next != NULL)
		tk = tk->next;
	return (tk);
}

t_word	*new_wle(char *s)
{
	t_word	*wle;

	wle = malloc(sizeof(t_word));
	if (wle == NULL)
		return (NULL);
	wle->word = ft_strdup(s);
	wle->next = NULL;
	return (wle);
}

void	append_wle(t_word *w, t_word **wl)
{
	t_word	*og;

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

void	append_redirect(t_redir *r, t_redir **rl)
{
	t_redir	*og;

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
