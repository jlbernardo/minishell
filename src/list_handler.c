/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:48:46 by julberna          #+#    #+#             */
/*   Updated: 2024/01/24 15:07:42 by iusantos         ###   ########.fr       */
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
