/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:47:27 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/03/08 16:44:39 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo_error(void);
int	check_flag(t_word *wl, int *flag);

int	echo(t_meta *meta, t_word *wl)
{
	int			flag;
	t_word		*temp;

	(void)meta;
	flag = LIE;
	temp = wl;
	temp = temp->next;
	while (check_flag(temp, &flag))
		temp = temp->next;
	while (temp)
	{
		if (write(STDOUT_FILENO, temp->word, ft_strlen(temp->word)) == -1)
			return (echo_error());
		temp = temp->next;
		if (temp)
		{
			if (write(STDOUT_FILENO, " ", 1) == -1)
				return (echo_error());
		}
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

int	check_flag(t_word *wl, int *flag)
{
	int		ret;
	char	*token;

	ret = LIE;
	if (wl && wl->word[0] == '-' && wl->word[1])
	{
		token = wl->word + 1;
		token = ft_strtrim(token, "n");
		if (ft_strlen(token) == 0)
		{
			*flag = TRUTH;
			ret = TRUTH;
		}
		free(token);
	}
	return (ret);
}
