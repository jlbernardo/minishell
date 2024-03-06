/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:15:05 by iusantos          #+#    #+#             */
/*   Updated: 2023/05/19 10:42:11 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			size;
	char			*strmapi;
	unsigned int	index;

	size = ft_strlen(s);
	strmapi = malloc((size + 1) * sizeof(char));
	if (strmapi == NULL)
		return (NULL);
	index = 0;
	while (s[index] != '\0')
	{
		strmapi[index] = (*f)(index, s[index]);
		index++;
	}
	strmapi[index] = '\0';
	return (strmapi);
}
