/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:32:55 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/03 19:58:24 by julberna         ###   ########.fr       */
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
	int		i;
	char	*temp;
	char	*to_free;
	char	*var_name;
	char	*var_value;

	i = 0;
	while ((*tokens)->literal[i] != '$')
		i++;
	var_name = ft_strdup(&(*tokens)->literal[i + 1]);
	var_value = getenv(var_name);
	temp = ft_calloc(ft_strlen((*tokens)->literal)
			- ft_strlen(var_name) - 1 + ft_strlen(var_value), sizeof(char));
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

/* int	has_valid_beginning(char *literal)
{
	while (*literal && *literal != '$')
		*literal++;
	if (!*literal)
		return (0);
	*literal++;
	if (ft_isalpha(*literal) || *literal == '_')
		return (1);
	return (0);
} */
