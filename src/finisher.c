/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finisher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:03:39 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/01/30 15:48:49 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	finisher(t_token *tokens, t_ast_node *ast)
{
	free_ast(ast);
	free_tokens(tokens);
}
