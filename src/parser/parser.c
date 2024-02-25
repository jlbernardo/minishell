/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:12:03 by julberna          #+#    #+#             */
/*   Updated: 2024/02/25 00:07:00 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser(t_meta *meta)
{
	t_token	*temp;

	if (!meta->tokens)
		return (LIE);
	remove_quotes(&meta->tokens);
	remove_empty_tokens(&meta->tokens);
	temp = meta->tokens;
	meta->ast = parse_pipeline(&meta->tokens, NULL);
	meta->tokens = temp;
	get_path(&meta->ast, meta->hash);
	if (meta->ast && meta->ast->success)
		return (TRUTH);
	return (LIE);
}

void	remove_quotes(t_token **tokens)
{
	int		i;
	int		len;
	char	quote;

	i = 0;
	if (!*tokens)
		return ;
	while ((*tokens)->literal[i] != '\0')
	{
		if (((*tokens)->literal[i] == '"' || (*tokens)->literal[i] == '\''))
		{
			quote = (*tokens)->literal[i];
			if (i > 0 && ((*tokens)->literal[i - 1] == '='))
				break ;
			len = ft_strlen((*tokens)->literal) - i;
			ft_memmove(&(*tokens)->literal[i], &(*tokens)->literal[i + 1], len);
			while ((*tokens)->literal[i] != quote)
				i++;
			len = ft_strlen((*tokens)->literal) - i;
			ft_memmove(&(*tokens)->literal[i], &(*tokens)->literal[i + 1], len);
			continue ;
		}
		i++;
	}
	remove_quotes(&(*tokens)->next);
}

void	remove_empty_tokens(t_token **tokens)
{
	t_token	*curr;

	curr = *tokens;
	if (!tokens || !*tokens)
		return ;
	if (!curr->literal)
	{
		*tokens = curr->next;
		free(curr->literal);
		free(curr);
		remove_empty_tokens(tokens);
	}
	else
		remove_empty_tokens(&curr->next);
}
