/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:38:30 by julberna          #+#    #+#             */
/*   Updated: 2024/02/14 22:19:45 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	int		control;
	t_ast	*ast;
	t_token	*tokens;
	t_hash	**ht;

	ht = ft_calloc(HT_SIZE, sizeof(t_hash *));
	add_env_to_ht(__environ, ht);
	control = 42;
	while (control)
	{
		if (lexer(&tokens, &ast))
			parser(tokens, &ast, ht);
		finisher(tokens, ast);
	}
	free_ht(ht);
	return (0);
}
