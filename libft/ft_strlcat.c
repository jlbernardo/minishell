/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:09:40 by iusantos          #+#    #+#             */
/*   Updated: 2023/05/23 11:20:06 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	counter;

	counter = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (size == 0)
		return (src_len);
	if (size < dst_len + 1)
		return (size + src_len);
	while (src[counter] != '\0' && counter < size - dst_len - 1)
	{
			dst[dst_len + counter] = src[counter];
			counter++;
	}
	dst[dst_len + counter] = '\0';
	return (dst_len + src_len);
}
