/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:32:01 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/19 21:08:00 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sort_vars(t_word **vars, t_word *first)
{
	t_word	*check;
	t_word	*first_p;
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

void	populate_sort_vars(t_hash **ht, t_word **vars)
{
	int		i;
	t_hash	*temp;

	i = 0;
	*vars = NULL;
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
