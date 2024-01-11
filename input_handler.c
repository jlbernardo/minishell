/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:18:04 by julberna          #+#    #+#             */
/*   Updated: 2024/01/11 20:36:52 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char *read_string(t_lexer *l)
{
	char	*string;
	char	quote;
	size_t	len;

	quote = l->ch;
	l->pos = l->read_pos++;
	while (l->input[l->read_pos] != quote && l->input[l->read_pos] != '\0')
		++l->read_pos;
	len = l->read_pos - l->pos;
	string = ft_substr(l->input, l->pos, len);
	l->pos = l->read_pos - 1;
	l->ch = l->input[l->read_pos];
	return (string);
}

char *read_word(t_lexer *l)
{
	char *identifier;
	size_t len;

	while (ft_notspace(l->input[l->read_pos]))
		++l->read_pos;
	len = l->read_pos - l->pos;
	identifier = ft_substr(l->input, l->pos, len);
	l->pos = l->read_pos - 1;
	return (identifier);
}

int	is_operand(char ch)
{
	if (ch == '>' || ch == '<' || ch == '|')
		return (1);
	return (0);
}