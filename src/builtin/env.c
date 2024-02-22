/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:22:09 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/22 14:48:35 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env(t_meta *meta, t_word *wl)
{
	int		i;
	t_hash	*temp;

	i = 0;
	(void)wl;
	while (i < HT_SIZE)
	{
		temp = meta->hash[i];
		while (meta->hash[i])
		{
			if (meta->hash[i]->value)
			{
				ft_putstr_fd(meta->hash[i]->name, 1);
				ft_putchar_fd('=', 1);
				ft_putendl_fd(meta->hash[i]->value, 1);
			}
			meta->hash[i] = meta->hash[i]->next;
		}
		meta->hash[i] = temp;
		i++;
	}
	return (0);
}
