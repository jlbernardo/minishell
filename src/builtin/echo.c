/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:47:27 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/22 14:49:23 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo_err(void);
int	check_flag(t_word *wl);

int	echo(t_meta *meta, t_word *wl)
{
	int			ret;
	t_word		*temp;
	const int	flag = check_flag(wl);

	(void)meta;
	temp = wl;
	temp = temp->next;
	if (flag)
		temp = temp->next;
	while (temp)
	{
		ret = write(1, temp->word, ft_strlen(temp->word));
		if (ret == -1)
			return (echo_err());
		temp = temp->next;
		if (temp)
			ret = write(1, " ", 1);
		if (ret == -1)
			return (echo_err());
	}
	if (!flag)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

int	echo_err(void)
{
	perror("minishell: echo");
	return (-1);
}

int	check_flag(t_word *wl)
{
	if (!ft_strcmp(wl->next->word, "-n"))
		return (1);
	return (0);
}
