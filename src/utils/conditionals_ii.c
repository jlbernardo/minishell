/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditionals_ii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:04:50 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/03/08 15:34:06 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c > 7 && c < 14))
		return (TRUTH);
	return (LIE);
}

int	valid_variable(char *literal)
{
	int	i;

	i = 0;
	if (literal[i] != '_' && !ft_isalpha(literal[i]))
		return (LIE);
	i++;
	while (literal[i] && literal[i] != '=')
	{
		if (literal[i] != '_' && !ft_isalnum(literal[i]))
			return (LIE);
		i++;
	}
	return (TRUTH);
}

int	is_readonly(char *literal)
{
	int			i;
	const char	*read_only[7] = {"BASHOPTS", "BASH_VERSINFO", "EUID",
		"PPID", "SHELLOPTS", "UID", NULL};

	i = 0;
	while (read_only[i])
	{
		if (ft_strcmp(read_only[i], literal) == 0)
			return (TRUTH);
		i++;
	}
	return (LIE);
}

int	valid_number(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isdigit(arg[i]) && arg[i] != '+' && arg[i] != '-')
		return (LIE);
	i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (LIE);
		i++;
	}
	return (TRUTH);
}
