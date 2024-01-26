/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:44:49 by julberna          #+#    #+#             */
/*   Updated: 2024/01/26 19:49:30 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	lexer(t_token **tokens)
{
	char	*input;
	t_lexer	lex;

	*tokens = NULL;
	input = readline("$> ");
	set_lexer(&lex, input);
	while (lex.read_pos < lex.size)
	{
		read_char(&lex);
		find_token(&lex, tokens, 1);
	}
	free(input);
}

void	set_lexer(t_lexer *lex, char *input)
{
	lex->input = input;
	lex->pos = 0;
	lex->read_pos = 0;
	lex->ch = 0;
	lex->size = ft_strlen(input);
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
			str = read_quoted(lex, 0);
		else
			str = read_unquoted(lex);
		new_token(tokens, WORD, str);
	}
	return (free(str));
}
