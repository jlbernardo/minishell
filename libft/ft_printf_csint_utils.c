/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_csint_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:10:55 by iusantos          #+#    #+#             */
/*   Updated: 2023/07/28 10:39:51 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	prtf_putchar(char c)
{
	size_t	length;

	length = 1;
	ft_putchar_fd(c, 1);
	return (length);
}

size_t	prtf_putstr(char *str)
{
	size_t	length;

	if (str == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	length = ft_strlen(str);
	ft_putstr_fd(str, 1);
	return (length);
}

size_t	print_int(int nbr)
{
	size_t	length;
	char	*str;

	str = ft_itoa(nbr);
	length = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (length);
}

size_t	count_digit_base(unsigned long n, unsigned int base)
{
	size_t	counter;

	counter = 1;
	while (n / base != 0)
	{
		counter++;
		n = n / base;
	}
	return (counter);
}
