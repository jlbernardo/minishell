/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:18:04 by julberna          #+#    #+#             */
/*   Updated: 2024/01/23 15:32:56 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	read_char(t_lexer *lex)
{
	if (lex->read_pos >= lex->size)
		lex->ch = 0;
	else
		lex->ch = lex->input[lex->read_pos];
	lex->pos = lex->read_pos++;
}

int	is_operand(char ch)
{
	if (ch == '>' || ch == '<' || ch == '|')
		return (1);
	return (0);
}

char	*read_unquoted(t_lexer *lex)
{
	char	*string;
	size_t	len;

	while (ft_notspace(lex->input[lex->read_pos])
		&& !is_operand(lex->input[lex->read_pos]))
		++lex->read_pos;
	len = lex->read_pos - lex->pos;
	string = ft_substr(lex->input, lex->pos, len);
	lex->pos = lex->read_pos - 1;
	return (string);
}

char	*read_quoted(t_lexer *l)
{
	char	*string;
	char	quote;
	size_t	len;

	quote = l->ch;
	l->read_pos++;
	while (l->input[l->read_pos] != ' ' && !is_operand(l->input[l->read_pos]) 
			&& l->input[l->read_pos] != '\0')
		++l->read_pos;
	l->read_pos++;
	len = l->read_pos - l->pos;
	string = ft_substr(l->input, l->pos, len);
	l->pos = l->read_pos - 1;
	l->ch = l->input[l->read_pos];
	return (string);
}
