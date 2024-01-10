/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:44:49 by julberna          #+#    #+#             */
/*   Updated: 2024/01/10 17:21:59 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	set_lexer(t_lexer *lexer, char *input)
{
	lexer->input = input;
	lexer->pos = 0;
	lexer->read_pos = 0;
	lexer->ch = 0;
	lexer->size = ft_strlen(input);
}

void	read_char(t_lexer *l)
{
	if (l->read_pos >= l->size)
		l->ch = 0;
	else
		l->ch = l->input[l->read_pos];
	l->pos = l->read_pos++;
}
