/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:48:46 by julberna          #+#    #+#             */
/*   Updated: 2024/01/24 20:08:10 by julberna         ###   ########.fr       */
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

t_wl_element	*new_wle(char *s)
{
	t_wl_element	*wle;

	wle = malloc(sizeof(t_wl_element));
	if (wle == NULL)
		return (NULL);
	wle->word = ft_strdup(s);
	wle->next = NULL;
	return (wle);
}

void	append_wle(t_wl_element *w, t_wl_element **wl)
{
	t_wl_element	*og;

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
