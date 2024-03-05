/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:35:49 by iusantos          #+#    #+#             */
/*   Updated: 2023/05/25 10:51:11 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node_ptr;

	new_node_ptr = (t_list *) malloc(sizeof(t_list));
	if (!new_node_ptr)
		return (NULL);
	new_node_ptr->content = content;
	new_node_ptr->next = NULL;
	return (new_node_ptr);
}
