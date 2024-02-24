/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:18:04 by julberna          #+#    #+#             */
/*   Updated: 2024/02/24 00:46:14 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	read_char(t_lexer *lex)
{
	if (lex->read_pos >= lex->size)
		lex->ch = 0;
	else
	{
		if (lex->input[lex->read_pos] < 0)
		{
			lex->pos = lex->read_pos;
			lex->ch = lex->input[lex->read_pos++];
			lex->read_pos++;
		}
		else
		{
			lex->ch = lex->input[lex->read_pos];
			lex->pos = lex->read_pos++;
		}
	}
}

int	is_operand(char ch)
{
	if (ch == '>' || ch == '<' || ch == '|')
		return (1);
	return (0);
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

char	*read_unquoted(t_lexer *l, char quote, int s_open, int d_open)
{
	char	ch;
	char	*string;
	size_t	len;

	while (ft_notspace(l->input[l->read_pos])
		&& !is_operand(l->input[l->read_pos]))
	{
		if (l->input[l->read_pos] == '"'
			|| l->input[l->read_pos] == '\'')
		{
			update_quote(l->input[l->read_pos], &s_open, &d_open, &quote);
			ch = l->input[++l->read_pos];
			while (ch != '\0' && !((s_open % 2 == 0 && d_open % 2 == 0)
					&& (l->input[l->read_pos + 1] == ' ' || is_operand(ch)
						|| l->input[l->read_pos + 1] == '\0')))
			{
				if (s_open % 2 != 0 || d_open % 2 != 0)
					update_quote(ch, &s_open, &d_open, &quote);
				ch = l->input[++l->read_pos];
				update_quote(ch, &s_open, &d_open, &quote);
			}
		}
		++l->read_pos;
	}
	len = l->read_pos - l->pos;
	string = ft_substr(l->input, l->pos, len);
	l->pos = l->read_pos - 1;
	if (s_open % 2 != 0 || d_open % 2 != 0)
		l->success = LIE;
	return (string);
}

char	*read_quoted(t_lexer *l, char quote, int s_open, int d_open)
{
	char	ch;
	char	*string;

	update_quote(l->ch, &s_open, &d_open, &quote);
	ch = l->input[l->read_pos];
	while (ch != '\0' && !((s_open % 2 == 0 && d_open % 2 == 0)
			&& (l->input[l->read_pos + 1] == ' ' || is_operand(ch)
				|| l->input[l->read_pos + 1] == '\0')))
	{
		if (s_open % 2 != 0 || d_open % 2 != 0)
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
