/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:07:13 by iusantos          #+#    #+#             */
/*   Updated: 2023/05/24 08:45:54 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns a substr of *s, starting from start (inclusive) of maximum
// length of len. Mallocs appropriately.
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*cpy_from;
	size_t	substr_max_length;

	if (start >= ft_strlen(s))
	{
		substr = malloc(sizeof(char));
		substr[0] = '\0';
		return (substr);
	}
	substr_max_length = ft_strlen(s) - start;
	if (substr_max_length < len)
		substr = malloc((substr_max_length + 1) * sizeof(char));
	else
		substr = malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	cpy_from = (char *)&s[start];
	ft_strlcpy(substr, cpy_from, len + 1);
	return (substr);
}
