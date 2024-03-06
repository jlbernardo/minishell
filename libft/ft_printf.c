/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:54:04 by iusantos          #+#    #+#             */
/*   Updated: 2023/07/28 10:39:05 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	size_t	index;
	size_t	ret_len;
	va_list	args;
	char	next_char;

	if (format == 0)
		return (-1);
	ret_len = ft_strlen(format);
	va_start(args, format);
	index = 0;
	while (format[index] != '\0')
	{
		if (format[index] == '%')
		{
			ret_len--;
			next_char = format[index + 1];
			ret_len += print_accordingly(next_char, args);
			index++;
		}
		else
			ft_putchar_fd(format[index], 1);
		index++;
	}
	va_end(args);
	return (ret_len);
}

size_t	print_accordingly(char c, va_list args)
{
	if (c == '%')
		return (prtf_putchar('%') - 1);
	if (c == 'c')
		return (prtf_putchar(va_arg(args, int)) - 1);
	if (c == 's')
		return (prtf_putstr(va_arg(args, char *)) - 1);
	if (c == 'i' || c == 'd')
		return (print_int(va_arg(args, int)) - 1);
	if (c == 'u')
		return (print_uint(va_arg(args, unsigned int)) - 1);
	if (c == 'x')
		return (print_hex(va_arg(args, unsigned int), 'l') - 1);
	if (c == 'X')
		return (print_hex(va_arg(args, unsigned int), 'u') - 1);
	if (c == 'p')
		return (print_voidp(va_arg(args, unsigned long)) - 1);
	return (0);
}
