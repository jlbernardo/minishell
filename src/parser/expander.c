/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:32:55 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/03/05 16:30:59 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_variable(char **input, t_meta *meta)
{
	if (has_variable(*input))
	{
		replace_variable(input, meta->hash);
		if (has_variable(*input))
			expand_variable(input, meta);
	}
}

void	replace_variable(char **input, t_hash **hash)
{
	int		i;
	int		len;
	char	*temp;
	char	*var_name;
	char	*var_value;

	i = 0;
	var_name = get_variable_name(*input, 0, 0, &i);
	var_value = grab_value(var_name, hash);
	temp = ft_strdup(*input);
	len = ft_strlen(temp) - ft_strlen(var_name) + ft_strlen(var_value);
	free(*input);
	*input = ft_calloc(len, sizeof(char));
	ft_strlcat(*input, temp, i);
	if (var_value)
		ft_strlcat(*input, var_value, \
			ft_strlen(*input) + ft_strlen(var_value) + 1);
	len = i + ft_strlen(var_name);
	ft_strlcat(*input, &temp[i + ft_strlen(var_name)], \
		ft_strlen(*input) + ft_strlen(&temp[len]) + 1);
	free(temp);
	free(var_name);
	free(var_value);
}

char	*get_variable_name(char *literal, int dq, int sq, int *i)
{
	int		j;
	char	*var;

	while (literal[*i])
	{
		if (literal[*i] == '"' && sq % 2 == 0)
			dq++;
		else if (literal[*i] == '\'' && dq % 2 == 0)
			sq++;
		if (literal[*i] == '$' && sq % 2 == 0)
			break ;
		(*i)++;
	}
	j = ++(*i);
	if (literal[j] && (ft_isalpha(literal[j]) || literal[j] == '_'))
	{
		while (literal[j] && (ft_isalnum(literal[j]) || literal[j] == '_'))
			j++;
	}
	if (j - *i < 1)
		j++;
	var = ft_substr(literal, *i, j - *i);
	return (var);
}
