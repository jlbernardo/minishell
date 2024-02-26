/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finisher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:03:39 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/25 18:34:29 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	finisher(t_meta meta, char *flag, int exit_code)
{
	if (ft_strchr(flag, 'A'))
		free_ast(meta.ast);
	if (ft_strchr(flag, 'T'))
		free_tokens(meta.tokens);
	if (ft_strchr(flag, 'H'))
		free_hash(meta.hash);
	if (ft_strchr(flag, 'E'))
		exit(exit_code);
}
