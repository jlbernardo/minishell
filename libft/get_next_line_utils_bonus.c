/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:54:04 by iusantos          #+#    #+#             */
/*   Updated: 2023/07/27 14:53:39 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	ret_str_len;
	char	*ret_str;
	char	*real_ret_str;
	char	*og_s1;

	if (s1 == NULL)
	{
		s1 = malloc(1 * sizeof(char *));
		*s1 = '\0';
	}
	og_s1 = s1;
	ret_str_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret_str = (char *) malloc(ret_str_len * sizeof(char));
	real_ret_str = ret_str;
	while (*s1 != '\0')
		*ret_str++ = *s1++;
	while (*s2 != '\0')
		*ret_str++ = *s2++;
	*ret_str = '\0';
	free(og_s1);
	return (real_ret_str);
}

//returns the index of the first newline char in the string. If there's no
//newline char in the string, returns -1.
int	find_first_newline(char *s1)
{
	int	index;

	if (s1 == NULL)
		return (-1);
	index = 0;
	while (s1[index] != '\0')
	{
		if (s1[index] == '\n')
			return (index);
		index++;
	}
	return (-1);
}
