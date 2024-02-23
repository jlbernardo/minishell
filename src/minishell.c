/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:38:30 by julberna          #+#    #+#             */
/*   Updated: 2024/02/22 11:19:43 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	set_meta(t_meta *meta, char **__environ)
{
	meta->hash = ft_calloc(HT_SIZE, sizeof(t_hash *));
	add_env_to_ht(__environ, meta->hash);
}

int	main(void)
{
	char	*debug_string;
	t_meta	meta;
	int		control;

	set_meta(&meta, __environ);
	control = 42;
	while (control)
	{
		if (lexer(&meta))
			if (parser(&meta))
				executor(&meta);
		finisher(meta);
		control = 0;
	}
	debug_string = grab_value("?", meta.hash);
	ft_printf("exit status: %s\n", debug_string);
	free(debug_string);
	free_ht(meta.hash);
	return (0);
}
