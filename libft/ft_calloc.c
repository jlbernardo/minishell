/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:42:12 by iusantos          #+#    #+#             */
/*   Updated: 2023/05/25 15:44:25 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*ptr;
	size_t	size;

	if (nelem == 0 || elsize == 0)
		return (malloc(0));
	size = nelem * elsize;
	if (size / nelem != elsize)
		return (NULL);
	ptr = malloc(size * sizeof(char));
	if (!ptr)
	{
		return (NULL);
	}
	ft_bzero(ptr, size);
	return (ptr);
}
