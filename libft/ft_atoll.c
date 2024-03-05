/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:15:46 by iusantos          #+#    #+#             */
/*   Updated: 2023/11/14 15:38:42 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (c);
	else
		return (0);
}

long long	ft_atoll(const char *nptr)
{
	int			sign;
	long long	number;

	sign = 1;
	number = 0;
	while (ft_isspace(*nptr) != 0)
		nptr++;
	if (*nptr == 45 || *nptr == 43)
	{
		if (*nptr == 45)
			sign = sign * -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		number = number * 10;
		number = number + (*nptr - '0');
		nptr++;
	}
	return (number * sign);
}
