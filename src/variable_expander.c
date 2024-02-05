/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:32:55 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/05 16:36:24 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	expand_variables(t_token **tokens)
{
	if (!*tokens)
		return ;
	if ((*tokens)->type != REDIRECT && has_variable((*tokens)->literal))
	{
		replace_variable(tokens);
		if (has_variable((*tokens)->literal))
			expand_variables(*tokens);
	}
	expand_variables((*tokens)->next);
}

void	replace_variable(t_token **tokens)
{
	char	*var_name;
	char	*var_value;

	var_name = get_variable_name((*tokens)->literal);
	var_value = get_variable_value((*tokens)->literal);
}

char	*get_variable_name(char *literal)
{
	int		i;
	int		j;
	int		len;
	char	*var;

	i = 0;
	while (literal[i] != '$')
		i++;
	i++;
	j = i;
	if (!ft_isalpha(literal[j]) || literal[j] != '_')
		return (NULL);
	j++;
	while (ft_isalnum(literal[j]) || literal[j] == '_')
		j++;
	len = j - i + 1;
	var = ft_calloc(len, sizeof(char));
	var = ft_strnstr(&literal[i], var, len);
	return (var);
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
