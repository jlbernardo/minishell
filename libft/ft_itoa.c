/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:37:12 by iusantos          #+#    #+#             */
/*   Updated: 2023/05/19 16:49:54 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	digit_counter(long n)
{
	size_t	counter;

	counter = 1;
	while (n / 10 != 0)
	{
		counter++;
		n = n / 10;
	}
	return (counter);
}

void	str_writer(long n, char *str, size_t length, int is_negative)
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
	index--;
	if (is_negative == 1)
		str[index] = '-';
}

char	*ft_itoa(int n)
{
	long	nbr;
	char	*str;
	size_t	length;
	int		is_negative;

	nbr = (long)n;
	is_negative = 0;
	length = digit_counter(nbr);
	if (nbr < 0)
	{
		length++;
		nbr = nbr * -1;
		is_negative = 1;
	}
	str = malloc((length + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str_writer(nbr, str, length, is_negative);
	return (str);
}
