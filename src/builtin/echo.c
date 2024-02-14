/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:47:27 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/14 00:02:38 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo_err(void);
int	check_flag(t_token *tokens);

int	echo(t_token *tokens)
{
	int	ret;
	const int	flag = check_flag(tokens);

	tokens = tokens->next;
	if (flag)
		tokens = tokens->next;
	while (tokens)
	{
		ret = write(1, tokens->literal, ft_strlen(tokens->literal));
		if (ret == -1)
			return (echo_err());
		tokens = tokens->next;
		if (tokens)
			ret = write(1, " ", 1);
		if (ret == -1)
			return (echo_err());
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}

int	echo_err(void)
{
	perror("bash: echo");
	return (-1);
}

int	check_flag(t_token *tokens)
{
	if (!ft_strcmp(tokens->next->literal, "-n"))
		return (1);
	return (0);
}
