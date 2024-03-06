/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:09:40 by iusantos          #+#    #+#             */
/*   Updated: 2024/03/05 21:12:57 by Juliany Ber      ###   ########.fr       */
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
