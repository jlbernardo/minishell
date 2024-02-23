/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:12:03 by julberna          #+#    #+#             */
/*   Updated: 2024/02/23 17:01:30 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	parser(t_meta *meta)
{
	t_token	*temp;

	if (!meta->tokens)
		return (LIE);
	expand_variables(&meta->tokens, meta);
	remove_quotes(&meta->tokens);
	remove_empty_tokens(&meta->tokens);
	temp = meta->tokens;
	meta->ast = parse_pipeline(&meta->tokens, NULL);
	get_path(&meta->ast, meta->hash);
	meta->tokens = temp;
	if (meta->ast && meta->ast->success)
		return (TRUTH);
	return (LIE);
}

void	remove_empty_tokens(t_token **tokens)
{
	t_token	*curr;

	curr = *tokens;
	if (!tokens || !*tokens)
		return ;
	if (!curr->literal || ft_strlen(curr->literal) == 0)
	{
		*tokens = curr->next;
		free(curr->literal);
		free(curr);
		remove_empty_tokens(tokens);
	}
	else
		remove_empty_tokens(&curr->next);
}

void	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", \
		STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}
