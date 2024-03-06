/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:47:45 by iusantos          #+#    #+#             */
/*   Updated: 2023/05/25 14:42:49 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Returns the number of elements in a list of nodes.
//Runs through the list:
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		counter;
	t_list	*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	counter = 1;
	while (tmp->next != NULL)
	{
		counter++;
		tmp = tmp->next;
	}
	return (counter);
}
