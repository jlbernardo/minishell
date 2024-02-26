/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:38:30 by julberna          #+#    #+#             */
/*   Updated: 2024/02/25 23:07:01 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	char	*ret;
	t_meta	meta;

	signal_handler();
	set_meta(&meta, __environ);
	while (42)
	{
		if (lexer(&meta))
			if (parser(&meta))
				executor(&meta);
		ret = grab_value("?", meta.hash);
		ft_printf("Return value: %s\n", ret);
		finisher(meta, "AT", EXIT_SUCCESS);
		free(ret);
	}
	finisher(meta, "HE", EXIT_SUCCESS);
}
