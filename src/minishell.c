/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:38:30 by julberna          #+#    #+#             */
/*   Updated: 2024/02/02 12:14:20 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	int			control;
	t_token		*tokens;
	t_ast_node	*ast;
	t_ht_entry	**env_vars;

	env_vars = ft_calloc(HT_SIZE, sizeof(t_ht_entry *));
	control = 42;
	while (control)
	{
		if (lexer(&tokens, &ast))
			parser(tokens, &ast);
		finisher(tokens, ast);
	}
	return (0);
}
