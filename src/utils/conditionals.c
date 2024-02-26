/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditionals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:44:26 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/25 18:47:09 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_operand(char ch)
{
	if (ch == '>' || ch == '<' || ch == '|')
		return (TRUTH);
	return (LIE);
}

int	quote_open(char ch, char next, int s_open, int d_open)
{
	if (ch != '\0' && !((s_open % 2 == 0 && d_open % 2 == 0)
			&& (next == ' ' || is_operand(ch) || next == '\0')))
		return (TRUTH);
	return (LIE);
}

int	has_other_pipes(t_token *tokens)
{
	tokens = tokens->next;
	if (tokens == NULL)
		return (LIE);
	while (tokens != NULL)
	{
		if (!ft_strncmp(tokens->literal, "|", 1))
			return (TRUTH);
		tokens = tokens->next;
	}
	return (LIE);
}

int	is_builtin(char *cmd)
{
	int					i;
	static const char	*builtins[7] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
	};

	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(cmd, builtins[i]))
			return (TRUTH);
		i++;
	}
	return (LIE);
}

int	has_variable(char *literal)
{
	int	d_quote;
	int	s_quote;

	d_quote = 0;
	s_quote = 0;
	while (*literal)
	{
		if (*literal == '"' && s_quote % 2 == 0)
			d_quote++;
		else if (*literal == '\'' && d_quote % 2 == 0)
			s_quote++;
		else if (*literal == '$'
			&& (ft_isalnum(*(literal + 1)) || *(literal + 1) == '_')
			&& (s_quote % 2 == 0))
			return (TRUTH);
		literal++;
	}
	return (LIE);
}
