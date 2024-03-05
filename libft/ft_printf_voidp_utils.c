/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_voidp_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:44:54 by iusantos          #+#    #+#             */
/*   Updated: 2023/07/28 10:40:49 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	write_pref_hex_str(unsigned long n, char *str, size_t length)
{
	size_t	index;
	char	base[17];

	ft_memcpy(base, "0123456789abcdef", 17);
	index = length;
	str[index] = '\0';
	index--;
	while (n / 16 != 0)
	{
		str[index] = base[n % 16];
		index--;
		n = n / 16;
	}
	str[index--] = base[n % 16];
	str[index--] = 'x';
	str[index] = '0';
}

char	*ultoa(unsigned long n)
{
	char	*str;
	size_t	length;

	length = count_digit_base(n, 16);
	str = malloc((length + 3) * sizeof(char));
	if (str == NULL)
		return (NULL);
	write_pref_hex_str(n, str, length + 2);
	return (str);
}

size_t	print_voidp(unsigned long p)
{
	size_t	length;
	char	*str;

	if (p == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	str = NULL;
	str = ultoa(p);
	length = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (length);
}
