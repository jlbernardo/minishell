/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:51:02 by iusantos          #+#    #+#             */
/*   Updated: 2023/05/24 10:51:05 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*ptr;

	ptr = NULL;
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			ptr = (unsigned char *)s;
		s++;
	}
	if (*s == '\0' && (unsigned char)c == '\0')
		ptr = (unsigned char *)s;
	return ((char *)ptr);
}
