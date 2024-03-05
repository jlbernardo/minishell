/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:18:04 by julberna          #+#    #+#             */
/*   Updated: 2024/03/04 22:01:28 by Juliany Ber      ###   ########.fr       */
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

char	*read_unquoted(t_lexer *lex)
{
	char	ch;
	char	*string;
	int		lex_pos;

	string = NULL;
	lex_pos = lex->pos;
	ch = lex->input[lex->read_pos];
	while (ch && ft_notspace(ch) && !is_operand(ch))
	{
		if (ch == '"' || ch == '\'')
		{
			lex->ch = ch;
			ch = lex->input[++lex->read_pos];
			string = read_quoted(lex, ch, 0, 0);
			break ;
		}
		ch = lex->input[++lex->read_pos];
	}
	if (!string)
		string = ft_substr(lex->input, lex_pos, lex->read_pos - lex_pos);
	lex->pos = lex->read_pos - 1;
	lex->ch = lex->input[lex->read_pos];
	return (string);
}

char	*read_quoted(t_lexer *lex, char quote, int sq, int dq)
{
	char	ch;
	char	*string;

	update_quote(lex->ch, &sq, &dq, &quote);
	ch = lex->input[lex->read_pos];
	update_quote(ch, &sq, &dq, &quote);
	while (ch && (quote_open(sq, dq) || (ft_notspace(ch) && !is_operand(ch))))
	{
		ch = lex->input[++lex->read_pos];
		update_quote(ch, &sq, &dq, &quote);
	}
	if (ch != '\0' && (ft_notspace(ch) && !is_operand(ch)))
		lex->read_pos++;
	string = ft_substr(lex->input, lex->pos, lex->read_pos - lex->pos);
	lex->pos = lex->read_pos - 1;
	lex->ch = lex->input[lex->read_pos];
	if (sq % 2 != 0 || dq % 2 != 0)
		lex->success = LIE;
	return (string);
}

char	*prompt_decision(t_meta *meta, char **user)
{
	char	*temp;
	char	*exit_code;
	char	*error_code;

	exit_code = grab_value("?", meta->hash);
	if (!*user)
		*user = ft_strdup("Voldemort ☠");
	if (last_exit(meta) == 0)
		error_code = ft_strdup("\033[1;32m[✔]\033[0m");
	else
	{
		error_code = ft_strdup("\033[1;31m[✖");
		temp = ft_strjoin(error_code, exit_code);
		free(error_code);
		error_code = ft_strjoin(temp, "]\033[0m");
		free(temp);
	}
	free(exit_code);
	return (error_code);
}
