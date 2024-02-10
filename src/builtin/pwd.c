/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:30:55 by julberna          #+#    #+#             */
/*   Updated: 2024/02/10 18:21:07 by julberna         ###   ########.fr       */
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
		return (0);
	}
	perror("bash: pwd");
	return (1);
}
