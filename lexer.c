/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:44:49 by julberna          #+#    #+#             */
/*   Updated: 2024/01/11 20:55:48 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	lexer(t_token **tokens)
{
	char	*input;
	t_lexer	*lex;

	*tokens = ft_calloc(1, sizeof(t_token *));
	*input = readline("$>");
	set_lexer(&lex, input);
	while(lex->read_pos <= lex->size)
	{
		read_char(&lex);
		find_token(&lex, tokens);
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

void	read_char(t_lexer *lex)
{
	if (lex->read_pos >= lex->size)
		lex->ch = 0;
	else
		lex->ch = lex->input[lex->read_pos];
	lex->pos = lex->read_pos++;
}

void	*find_token(t_lexer *lex, t_token **tokens)
{
	char	*str;
	int		size;

	if (is_operand(lex->ch))
	{
		size = 1;
		if ((lex->ch == '>' || lex->ch == '<') && 
			lex->input[lex->read_pos] == lex->ch)
			size++;
		ft_strlcpy(str, lex->input[lex->pos], size); //check correct start
		new_token(tokens, "operand", str);
	}
	else
	{
		if (lex->ch == '"' || lex->ch == '\'')
			str = read_string(lex);
		else
			str = read_word(lex);
		new_token(tokens, "word", str);
	}
	return ;
}
