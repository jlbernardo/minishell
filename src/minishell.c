/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:38:30 by julberna          #+#    #+#             */
/*   Updated: 2024/02/10 16:03:22 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	int		control;
	t_ast	*ast;
	t_token	*tokens;
	t_hash	**env_vars;

	env_vars = ft_calloc(HT_SIZE, sizeof(t_hash *));
	add_env_to_ht(__environ, env_vars);
	control = 42;
	while (control)
	{
		if (lexer(&tokens, &ast))
			parser(tokens, &ast, env_vars);
		finisher(tokens, ast);
	}
	free_ht(env_vars);
	return (0);
}
