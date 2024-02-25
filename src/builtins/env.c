/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:22:09 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/25 00:07:00 by Juliany Ber      ###   ########.fr       */
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
			if (meta->hash[i]->value && ft_strcmp(meta->hash[i]->name, "?"))
			{
				ft_putstr_fd(meta->hash[i]->name, STDOUT_FILENO);
				ft_putchar_fd('=', STDOUT_FILENO);
				ft_putendl_fd(meta->hash[i]->value, STDOUT_FILENO);
			}
			meta->hash[i] = meta->hash[i]->next;
		}
		meta->hash[i] = temp;
		i++;
	}
	return (EXIT_SUCCESS);
}
