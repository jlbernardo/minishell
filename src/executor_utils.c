/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:09:16 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/24 17:26:33 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	**stringfy(t_word *wl)
{
	char	**array;
	int		size;
	int		index;

	size = get_size(wl) + 1;
	array = ft_calloc(size, sizeof(char *));
	index = 0;
	while (wl->next != NULL)
	{
		array[index] = ft_strdup(wl->word);
		index++;
		wl = wl->next;
	}
	array[index] = ft_strdup(wl->word);
	return (array);
}

int	get_size(t_word *wl)
{
	int	nelem;

	nelem = 1;
	while (wl->next != NULL)
	{
		nelem++;
		wl = wl->next;
	}
	return (nelem);
}

void	close_all_fds(void)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		close(i);
		i++;
	}
}
