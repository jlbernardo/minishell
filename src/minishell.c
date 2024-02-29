/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:38:30 by julberna          #+#    #+#             */
/*   Updated: 2024/02/28 21:17:54 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	t_meta	meta;

	set_meta(&meta, __environ);
	while (42)
	{
		signal_handler();
		if (lexer(&meta))
			if (parser(&meta))
				executor(&meta);
		finisher(meta, "AT", EXIT_SUCCESS);
	}
	finisher(meta, "HE", last_exit(&meta));
}
