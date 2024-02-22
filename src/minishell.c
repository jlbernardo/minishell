/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:38:30 by julberna          #+#    #+#             */
/*   Updated: 2024/02/21 22:47:28 by Juliany Ber      ###   ########.fr       */
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
	t_meta	meta;
	int		control;

	set_meta(&meta, __environ);
	control = 42;
	while (control)
	{
		if (lexer(&meta.tokens, &meta.ast))
			if (parser(&meta))
				executor(meta.ast, &meta);
		finisher(meta.tokens, meta.ast);
		control = 0;
	}
	free_ht(meta.hash);
	return (0);
}
