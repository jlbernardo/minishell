/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:32:55 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/01/31 21:02:58 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* THE PLAN */
/* - Check if literal has '$'
   - Check if variable beginning is valid
     - if not, replace '&x' with 'empty' and keep the rest
   - Check if variable exists
     - if not, replace with 'empty'
	 - else, replace with variable value
   - Check if current literal has more '$'
     - if yes, recursive call with current token
   - Recursive call with next token */

void	expand_variables(t_token **tokens)
{
	if (!*tokens)
		return ;
	if ((*tokens)->type != REDIRECT && has_variable((*tokens)->literal)
		&& valid_variable((*tokens)->literal))
	{
		if (has_variable((*tokens)->literal))
			expand_variables(*tokens);
	}
	expand_variables((*tokens)->next);
}

int	valid_variable(char *literal)
{
	while (*literal != '$')
		*literal++;
	*literal++;
	if (*literal != '_' || !ft_isalpha(*literal))
		return (0);
	*literal++;
	while (*literal)
	{
		if (*literal != '_' || !ft_isalnum(*literal))
			return (0);
		*literal++;
	}
	return (1);
}

int	has_variable(char *literal)
{
	int	d_quote;
	int	s_quote;

	d_quote = 0;
	s_quote = 0;
	while (*literal)
	{
		if (*literal == '"')
			d_quote++;
		else if (*literal == '\'')
			s_quote++;
		else if (*literal == '$' && (!(d_quote % 2 == 0 && s_quote % 2 != 0)))
			return (1);
		*literal++;
	}
	return (0);
}
