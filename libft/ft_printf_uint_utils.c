/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uint_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:36:56 by iusantos          #+#    #+#             */
/*   Updated: 2023/07/28 10:40:34 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	write_str(long n, char *str, size_t length)
{
	size_t	index;

	index = length;
	str[index] = '\0';
	index--;
	while (n / 10 != 0)
	{
		str[index] = (n % 10) + 48;
		index--;
		n = n / 10;
	}
	str[index] = (n % 10) + 48;
}

char	*ft_uitoa(unsigned int n)
{
	char	*str;
	size_t	length;

	length = count_digit_base(n, 10);
	str = malloc((length + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	write_str(n, str, length);
	return (str);
}

size_t	print_uint(unsigned int nbr)
{
	size_t	length;
	char	*str;

	str = ft_uitoa(nbr);
	length = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (length);
}
