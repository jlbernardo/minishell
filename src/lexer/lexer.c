/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:44:49 by julberna          #+#    #+#             */
/*   Updated: 2024/03/04 14:06:22 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	lexer(t_meta *meta)
{
	char	*input;
	t_lexer	lex;

	meta->tokens = NULL;
	meta->ast = NULL;
	input = readline("$> ");
	if (g_received_signal == SIGINT)
		add_upd_hashtable("?", "130", meta->hash);
	if (!input)
		eof_basic(meta);
	add_history(input);
	expand_variable(&input, meta);
	set_lexer(&lex, input);
	while (lex.read_pos < lex.size && lex.success == TRUTH)
	{
		read_char(&lex);
		find_token(&lex, &meta->tokens, 1);
	}
	if (!lex.success)
		syntax_error(meta->tokens, meta);
	free(input);
	return (lex.success);
}

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

void	find_token(t_lexer *lex, t_token **tokens, int size)
{
	char	*str;

	if (lex->ch == ' ')
		return ;
	else if (is_operand(lex->ch))
	{
		if ((lex->ch == '>' || lex->ch == '<')
			&& lex->input[lex->read_pos] == lex->ch)
			size++;
		str = ft_calloc(size + 1, sizeof(char));
		ft_memcpy(str, &lex->input[lex->pos], size);
		new_token(tokens, REDIRECT, str);
		if (size > 1)
			lex->pos = lex->read_pos++;
	}
	else
	{
		if (lex->ch == '"' || lex->ch == '\'')
			str = read_quoted(lex, 0, 0, 0);
		else
			str = read_unquoted(lex);
		new_token(tokens, WORD, str);
	}
	return (free(str));
}
