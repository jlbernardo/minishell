/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:52:24 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/15 23:01:43 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export(t_token *tokens, t_hash **ht)
{
	int		size;
	t_list	*vars;

	size = get_ht_size(ht);
	populate(ht, &vars);
}

void	ordenate(t_list **vars)
{
	t_list	*temp;

	temp = *vars;
	
}

void	populate(t_hash **ht, t_list **vars)
{
	int		i;
	t_hash	**temp;

	i = 0;
	while (i < HT_SIZE)
	{
		temp = ht[i];
		while (ht[i])
		{
			ft_lstadd_back(vars, ft_lstnew((void *)ht[i]->name));
			ht[i] = ht[i]->next;
		}
		ht[i] = temp;
		i++;
	}
}

int	get_ht_size(t_hash **ht)
{
	int		i;
	int		size;
	t_hash	**temp;

	i = 0;
	size = 0;
	while (i < HT_SIZE)
	{
		temp = ht[i];
		while (ht[i])
		{
			size++;
			ht[i] = ht[i]->next;
		}
		ht[i] = temp;
		i++;
	}
	return (size);
}
