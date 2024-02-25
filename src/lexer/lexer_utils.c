/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:18:04 by julberna          #+#    #+#             */
/*   Updated: 2024/02/25 00:07:00 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_quote(char ch, int *sq, int *dq, char *quote)
{
	if (ch == '"' && *sq % 2 == 0)
	{
		*dq += 1;
		*quote = ch;
	}
	else if (ch == '\'' && *dq % 2 == 0)
	{
		*sq += 1;
		*quote = ch;
	}
}

char	*read_unquoted(t_lexer *l)
{
	char	ch;
	char	*string;
	int		l_pos;

	string = NULL;
	l_pos = l->pos;
	ch = l->input[l->read_pos];
	while (ch && ft_notspace(ch) && !is_operand(ch))
	{
		if (ch == '"' || ch == '\'')
		{
			l->ch = ch;
			ch = l->input[++l->read_pos];
			string = read_quoted(l, ch, 0, 0);
			break ;
		}
		ch = l->input[++l->read_pos];
	}
	if (!string)
		string = ft_substr(l->input, l_pos, l->read_pos - l_pos);
	l->pos = l->read_pos - 1;
	l->ch = l->input[l->read_pos];
	return (string);
}

char	*read_quoted(t_lexer *l, char quote, int sq, int dq)
{
	char	ch;
	char	*string;

	update_quote(l->ch, &sq, &dq, &quote);
	ch = l->input[l->read_pos];
	while (ch && quote_open(ch, l->input[l->read_pos + 1], sq, dq))
	{
		if (sq % 2 != 0 || dq % 2 != 0)
			update_quote(ch, &sq, &dq, &quote);
		ch = l->input[++l->read_pos];
		update_quote(ch, &sq, &dq, &quote);
	}
	if (ch == quote)
		l->read_pos++;
	string = ft_substr(l->input, l->pos, l->read_pos - l->pos);
	l->pos = l->read_pos - 1;
	l->ch = l->input[l->read_pos];
	if (sq % 2 != 0 || dq % 2 != 0)
		l->success = LIE;
	return (string);
}
