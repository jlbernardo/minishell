/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:32:55 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/07 16:01:07 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	expand_variables(t_token **tokens, t_hash **ht)
{
	if (!*tokens)
		return ;
	if ((*tokens)->type != REDIRECT && has_variable((*tokens)->literal))
	{
		replace_variable(tokens, ht);
		if (has_variable((*tokens)->literal))
			expand_variables(tokens, ht);
	}
	expand_variables(&(*tokens)->next, ht);
}

void	replace_variable(t_token **tokens, t_hash **ht)
{
	int		i;
	int		len;
	char	*temp;
	char	*var_name;
	char	*var_value;

	i = 0;
	var_name = get_variable_name((*tokens)->literal);
	var_value = grab_value(var_name, ht);
	temp = ft_strdup((*tokens)->literal);
	len = ft_strlen(temp) - ft_strlen(var_name) + ft_strlen(var_value);
	free((*tokens)->literal);
	while (temp[i] != '$')
		i++;
	(*tokens)->literal = ft_calloc(len, sizeof(char));
	ft_strlcat((*tokens)->literal, temp, i + 1);
	if (var_value)
		ft_strlcat((*tokens)->literal, var_value, ft_strlen((*tokens)->literal)
			+ ft_strlen(var_value) + 1);
	len = i + ft_strlen(var_name) + 1;
	ft_strlcat((*tokens)->literal, &temp[i + ft_strlen(var_name) + 1], \
		ft_strlen((*tokens)->literal) + ft_strlen(&temp[len]) + 1);
	free(temp);
	free(var_name);
	free(var_value);
}

char	*get_variable_name(char *literal)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	while (literal[i] != '$')
		i++;
	j = ++i;
	if (literal[j] && (ft_isalpha(literal[j]) || literal[j] == '_'))
	{
		while (literal[j] && (ft_isalnum(literal[j]) || literal[j] == '_'))
			j++;
	}
	if (j - i < 1)
		j++;
	var = ft_substr(literal, i, j - i);
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
		literal++;
	}
	return (0);
}
