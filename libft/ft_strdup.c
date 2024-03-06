/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:43:25 by iusantos          #+#    #+#             */
/*   Updated: 2023/05/24 10:44:23 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	size_t	counter;

	counter = 0;
	while (src[counter] != '\0')
	{
		dest[counter] = src[counter];
		counter++;
	}
	dest[counter] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*dst;
	size_t	size;

	size = ft_strlen(s) + 1;
	dst = malloc(size * sizeof(char));
	if (dst == NULL)
		return (NULL);
	ft_strcpy(dst, (char *) s);
	return (dst);
}
