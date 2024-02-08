/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:43:12 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/07 20:50:40 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
		if ((*tokens)->literal[i] == '"' || (*tokens)->literal[i] == '\'')
		{
			quote = (*tokens)->literal[i];
			len = ft_strlen((*tokens)->literal) - i;
			ft_memmove(&(*tokens)->literal[i], &(*tokens)->literal[i + 1], len);
			while ((*tokens)->literal[i] != quote)
				i++;
			len = ft_strlen((*tokens)->literal) - i;
			ft_memmove(&(*tokens)->literal[i], &(*tokens)->literal[i + 1], len);
		}
		i++;
	}
	remove_quotes(&(*tokens)->next);
}
