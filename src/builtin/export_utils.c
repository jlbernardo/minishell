/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:32:01 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/23 16:09:14 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	populate_sort_vars(t_hash **ht, t_word **vars)
{
	int		i;
	t_hash	*temp;

	i = 0;
	while (i < HT_SIZE)
	{
		temp = ht[i];
		while (ht[i])
		{
			append_wle(new_wle(ht[i]->name), vars);
			ht[i] = ht[i]->next;
		}
		ht[i] = temp;
		i++;
	}
}

void	sort_vars(t_word **vars, t_word *first, t_word *first_p)
{
	t_word	*check;
	t_word	*check_p;

	while (!sorted(*vars))
	{
		check = first->next;
		check_p = first;
		while (check)
		{
			if (ft_strcmp(first->word, check->word) > 0)
			{
				check_p->next = check->next;
				check->next = first;
				first = check;
				if (first_p)
					first_p->next = first;
				if (ft_strcmp((*vars)->word, first->word) > 0)
					*vars = first;
			}
			check_p = check;
			check = check->next;
		}
		first_p = first;
		first = first->next;
	}
}

void	print_export(t_word *vars, t_hash **ht)
{
	char	*value;

	while (vars)
	{
		if (ft_strcmp(vars->word, "_") == 0 || ft_strcmp(vars->word, "?") == 0)
		{
			vars = vars->next;
			continue ;
		}
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

int	sorted(t_word *vars)
{
	while (vars->next)
	{
		if (ft_strcmp(vars->word, vars->next->word) > 0)
			return (LIE);
		vars = vars->next;
	}
	return (TRUTH);
}

int	valid_variable(char *literal)
{
	int	i;

	i = 0;
	if (literal[i] != '_' && !ft_isalpha(literal[i]))
		return (0);
	i++;
	while (literal[i] && literal[i] != '=')
	{
		if (literal[i] != '_' && !ft_isalnum(literal[i]))
			return (0);
		i++;
	}
	return (1);
}
