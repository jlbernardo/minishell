/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:47:27 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/24 18:56:04 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo_error(void);
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
		ret = write(STDOUT_FILENO, temp->word, ft_strlen(temp->word));
		if (ret == -1)
			return (echo_error());
		temp = temp->next;
		if (temp)
			ret = write(STDOUT_FILENO, " ", 1);
		if (ret == -1)
			return (echo_error());
	}
	if (!flag)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}

int	echo_error(void)
{
	perror("minishell: echo");
	return (-1);
}

int	check_flag(t_word *wl)
{
	if (wl->next && !ft_strcmp(wl->next->word, "-n"))
		return (TRUTH);
	return (LIE);
}
