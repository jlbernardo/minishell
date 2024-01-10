/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:48:46 by julberna          #+#    #+#             */
/*   Updated: 2024/01/10 13:49:15 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_tk	*new_token(t_tk_type type, char *literal)
{
	t_tk *token;

	token = ft_calloc(1, sizeof(t_tk *));
	token->type = type;
	token->literal = ft_strdup(literal);
	token->next = NULL;
	return (token);
}
