/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moses_ii.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:31:50 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/28 20:58:53 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	safe_free(void *p)
{
	if (p == NULL)
		return ;
	free(p);
	p = NULL;
}

void	free_hash(t_hash **ht)
{
	unsigned int	i;

	i = 0;
	while (i < HT_SIZE)
	{
		if (ht[i] != NULL)
			free_ht_entry(ht[i]);
		i++;
	}
	safe_free(ht);
}

void	free_ht_entry(t_hash *ht)
{
	if (ht->next != NULL)
		free_ht_entry(ht->next);
	safe_free(ht->name);
	safe_free(ht->value);
	safe_free(ht);
}

void	free_str_array(char **array, int size)
{
	int	index;

	if (array == NULL)
		return ;
	index = 0;
	while (index <= size)
	{
		free(array[index]);
		index++;
	}
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
