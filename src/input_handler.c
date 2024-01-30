/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:18:04 by julberna          #+#    #+#             */
/*   Updated: 2024/01/29 19:07:31 by Juliany Ber      ###   ########.fr       */
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

void	update_quote(char ch, int *s_open, int *d_open, char *quote)
{
	if (ch == '"' && *s_open % 2 == 0)
	{
		*d_open += 1;
		*quote = ch;
	}
	else if (ch == '\'' && *d_open % 2 == 0)
	{
		*s_open += 1;
		*quote = ch;
	}
}

char	*read_quoted(t_lexer *l, char quote, int s_open, int d_open)
{
	char	ch;
	char	*string;

	update_quote(l->ch, &s_open, &d_open, &quote);
	ch = l->input[l->read_pos];
	while (!is_operand(ch) && ch != '\0'
		&& !((s_open % 2 == 0 && d_open % 2 == 0)
			&& (l->input[l->read_pos + 1] == ' '
				|| l->input[l->read_pos + 1] == '\0')))
	{
		if (s_open % 2 != 0 && d_open % 2 != 0)
			update_quote(ch, &s_open, &d_open, &quote);
		ch = l->input[++l->read_pos];
		update_quote(ch, &s_open, &d_open, &quote);
	}
	if (ch == quote)
		l->read_pos++;
	string = ft_substr(l->input, l->pos, l->read_pos - l->pos);
	l->pos = l->read_pos - 1;
	l->ch = l->input[l->read_pos];
	if (s_open % 2 != 0 || d_open % 2 != 0)
		l->success = LIE;
	return (string);
}
