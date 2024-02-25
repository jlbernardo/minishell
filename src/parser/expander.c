/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:32:55 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/25 00:07:00 by Juliany Ber      ###   ########.fr       */
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
	var_name = get_variable_name(*input);
	var_value = grab_value(var_name, hash);
	temp = ft_strdup(*input);
	len = ft_strlen(temp) - ft_strlen(var_name) + ft_strlen(var_value);
	free(*input);
	while (temp[i] != '$')
		i++;
	*input = ft_calloc(len, sizeof(char));
	ft_strlcat(*input, temp, i + 1);
	if (var_value)
		ft_strlcat(*input, var_value, \
			ft_strlen(*input) + ft_strlen(var_value) + 1);
	len = i + ft_strlen(var_name) + 1;
	ft_strlcat(*input, &temp[i + ft_strlen(var_name) + 1], \
		ft_strlen(*input) + ft_strlen(&temp[len]) + 1);
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
