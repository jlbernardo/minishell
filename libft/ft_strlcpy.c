/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:23:55 by iusantos          #+#    #+#             */
/*   Updated: 2023/05/23 11:34:42 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_size;
	size_t	counter;

	src_size = ft_strlen(src);
	if (size == 0)
		return (src_size);
	counter = 0;
	while (src[counter] != '\0' && counter < size - 1)
	{
		dst[counter] = src[counter];
		counter++;
	}
	dst[counter] = '\0';
	return (src_size);
}
