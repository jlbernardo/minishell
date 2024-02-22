/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:30:55 by julberna          #+#    #+#             */
/*   Updated: 2024/02/22 14:44:17 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd(t_meta *meta, t_word *wl)
{
	char	*path;

	(void)meta;
	(void)wl;
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
