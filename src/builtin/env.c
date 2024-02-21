/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:22:09 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/21 16:19:58 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env(t_hash **ht)
{
	int		i;
	t_hash	*temp;

	i = 0;
	while (i < HT_SIZE)
	{
		temp = ht[i];
		while (ht[i])
		{
			if (ht[i]->value)
			{
				ft_putstr_fd(ht[i]->name, 1);
				ft_putchar_fd('=', 1);
				ft_putendl_fd(ht[i]->value, 1);
			}
			ht[i] = ht[i]->next;
		}
		ht[i] = temp;
		i++;
	}
	return (0);
}
