/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:47:27 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/12 19:25:12 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_flag(t_token *tokens);

int	echo(t_token *tokens)
{
	int	ret;
	int	flag;

	flag = check_flag(tokens);
	if (flag)
		tokens = tokens->next->next;
	else
		tokens = tokens->next;
	while (tokens)
	{
		ret = write(1, tokens->literal, ft_strlen(tokens->literal));
		if (ret == -1)
		{
			perror("bash: echo");
			return (ret);
		}
		tokens = tokens->next;
		if (tokens)
			ret = write(1, " ", 1);
		if (ret == -1)
		{
			perror("bash: echo");
			return (ret);
		}
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}

int	check_flag(t_token *tokens)
{
	if (!ft_strcmp(tokens->next->literal, "-n"))
		return (1);
	return (0);
}
