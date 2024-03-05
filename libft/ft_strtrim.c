/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:51:31 by iusantos          #+#    #+#             */
/*   Updated: 2023/05/24 10:51:35 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//ft_isinset returns 1 if c is containd in set, 0 otherwise
static int	ft_isinset(char c, char *set)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static int	ft_is_set_empty(char *set)
{
	if (*set == '\0')
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	index;
	size_t	trimmed_size;
	char	*trimmed_start;
	char	*trimmed_end;
	char	*trimmed;

	if (ft_is_set_empty((char *)set) == 1)
		return (ft_strdup(s1));
	trimmed_start = (char *)&s1[0];
	trimmed_end = (char *)&s1[ft_strlen(s1)];
	index = -1;
	while (ft_isinset(s1[++index], (char *) set) == 1 && s1[index] != '\0')
		trimmed_start = (char *)&s1[index + 1];
	if (s1[index] == '\0')
		return (ft_strdup(""));
	index = ft_strlen(s1);
	while (ft_isinset(s1[--index], (char *)set) == 1)
		trimmed_end = (char *)&s1[index];
	trimmed_size = trimmed_end - trimmed_start + 1;
	trimmed = malloc(trimmed_size);
	if (trimmed == NULL)
		return (NULL);
	ft_strlcpy(trimmed, trimmed_start, trimmed_size);
	return (trimmed);
}
