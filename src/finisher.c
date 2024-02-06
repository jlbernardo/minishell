/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finisher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:03:39 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/06 15:09:24 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	finisher(t_token *tokens, t_ast *ast, t_hash **env_vars)
{
	free_ast(ast);
	free_tokens(tokens);
	free_ht(env_vars);
}
