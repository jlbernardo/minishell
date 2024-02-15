/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:38:30 by julberna          #+#    #+#             */
/*   Updated: 2024/02/14 17:36:10 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	set_meta(t_meta *meta, char **__environ)
{
	meta->env_vars = ft_calloc(HT_SIZE, sizeof(t_hash *));
	add_env_to_ht(__environ, meta->env_vars);
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
			if (parser(meta.tokens, &meta.ast, meta.env_vars))
				executor(meta.ast, &meta);
		finisher(meta.tokens, meta.ast);
		control = 0;
	}
	free_ht(meta.env_vars);
	return (0);
}
