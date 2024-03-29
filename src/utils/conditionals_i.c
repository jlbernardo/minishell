/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditionals_i.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:44:26 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/03/08 17:31:05 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_operand(char ch)
{
	if (ch == '>' || ch == '<' || ch == '|')
		return (TRUTH);
	return (LIE);
}

int	quote_open(int s_open, int d_open)
{
	if (s_open % 2 == 0 && d_open % 2 == 0)
		return (LIE);
	return (TRUTH);
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
		else if (*literal == '$' && (s_quote % 2 == 0)
			&& (ft_isalnum(*(literal + 1)) || *(literal + 1) == '_'
				|| *(literal + 1) == '?' || *(literal + 1) == '\''
				|| (*(literal + 1) == '"' && (d_quote % 2 == 0))))
			return (TRUTH);
		literal++;
	}
	return (LIE);
}
