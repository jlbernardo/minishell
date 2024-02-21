/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:30:55 by julberna          #+#    #+#             */
/*   Updated: 2024/02/20 18:04:23 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd(void)
{
	char	*path;

	path = getcwd(NULL, PATH_MAX);
	if (path)
	{
		ft_putendl_fd(path, 1);
		free(path);
		return (EXIT_SUCCESS);
	}
	perror("minishell: pwd");
	return (EXIT_FAILURE);
}
