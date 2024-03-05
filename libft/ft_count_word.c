/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:47:55 by iusantos          #+#    #+#             */
/*   Updated: 2023/09/19 17:53:41 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	count_word(const char *s, char c)
{
	int	trigger;
	int	counter;

	trigger = 0;
	counter = 0;
	while (*s != '\0')
	{
		if (*s != c && trigger == 0)
		{
			counter++;
			trigger = 1;
		}
		if (*s == c)
			trigger = 0;
		s++;
	}
	return (counter);
}
