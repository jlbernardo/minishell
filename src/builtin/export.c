/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:52:24 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/19 21:01:11 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_export(t_word *vars, t_hash **ht);

int	export(t_token *tokens, t_hash **ht)
{
	int		len;
	char	*name;
	char	*value;
	t_word	*vars;

	tokens = tokens->next;
	if (tokens)
	{
		while (tokens)
		{
			len = ft_strchr(tokens->literal, '=') - tokens->literal;
			name = ft_substr(tokens->literal, 0, len);
			len = ft_strlen(tokens->literal) - len - 1;
			value = ft_substr(ft_strchr(tokens->literal, '='), 1, len);
			add_or_upd_ht_entry(name, value, ht);
			free(name);
			free(value);
			tokens = tokens->next;
		}
	}
	else
	{
		populate_sort_vars(ht, &vars);
		sort_vars(&vars, vars);
		print_export(vars, ht);
		free_wl2(vars);
	}
	return (0);
}

void	print_export(t_word *vars, t_hash **ht)
{
	char	*value;

	while (vars)
	{
		value = grab_value(vars->word, ht);
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(vars->word, 1);
		if (value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		free(value);
		vars = vars->next;
	}
}
