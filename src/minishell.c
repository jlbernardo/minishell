/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:38:30 by julberna          #+#    #+#             */
/*   Updated: 2024/02/06 18:19:31 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	int		control;
	t_ast	*ast;
	t_token	*tokens;
	t_hash	**env_vars;

	control = 42;
	env_vars = NULL;
	while (control)
	{
		if (lexer(&tokens, &ast))
			parser(tokens, &ast, &env_vars);
		finisher(tokens, ast, env_vars);
	}
	return (0);
}
