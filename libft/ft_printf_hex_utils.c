/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:37:25 by iusantos          #+#    #+#             */
/*   Updated: 2023/07/28 10:40:11 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	write_hex_str(unsigned long n, char *str, size_t length, char c)
{
	size_t	index;
	char	base[17];

	if (c == 'l')
		ft_memcpy(base, "0123456789abcdef", 17);
	if (c == 'u')
		ft_memcpy(base, "0123456789ABCDEF", 17);
	index = length;
	str[index] = '\0';
	index--;
	while (n / 16 != 0)
	{
		str[index] = base[n % 16];
		index--;
		n = n / 16;
	}
	str[index] = base[n % 16];
}

char	*uitohex(unsigned long n, char c)
{
	char	*str;
	size_t	length;

	length = count_digit_base(n, 16);
	str = malloc((length + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	write_hex_str(n, str, length, c);
	return (str);
}

size_t	print_hex(unsigned long n, char c)
{
	size_t	length;
	char	*str;

	str = uitohex(n, c);
	length = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (length);
}
