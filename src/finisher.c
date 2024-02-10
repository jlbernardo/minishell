/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finisher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:03:39 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/10 17:49:50 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	finisher(t_token *tokens, t_ast *ast)
{
	free_ast(ast);
	free_tokens(tokens);
}
