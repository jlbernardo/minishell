/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:46:28 by iusantos          #+#    #+#             */
/*   Updated: 2023/05/24 10:46:58 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	joined_size;
	char	*joined_str;

	joined_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined_str = malloc(joined_size * sizeof(char));
	if (joined_str == NULL)
		return (NULL);
	ft_strlcpy(joined_str, s1, joined_size);
	ft_strlcat(joined_str, s2, joined_size);
	return (joined_str);
}
