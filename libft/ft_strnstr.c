/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:39:45 by iusantos          #+#    #+#             */
/*   Updated: 2024/03/05 21:13:22 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcmp2(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	counter;

	counter = 0;
	if (little[counter] == '\0')
		return ((char *)big);
	while (big[counter] != '\0' && len - counter >= ft_strlen(little))
	{
		if (ft_strcmp2(little, &big[counter]) == 0)
			return ((char *)&big[counter]);
		counter++;
	}
	return (NULL);
}
