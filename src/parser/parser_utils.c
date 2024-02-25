/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 20:24:28 by julberna          #+#    #+#             */
/*   Updated: 2024/02/25 00:07:00 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redir	*new_redirect(t_token *tokens)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	if (ft_strncmp(tokens->literal, ">", 1) == 0)
		redir->type = REDOUT;
	else if (ft_strncmp(tokens->literal, ">>", 2) == 0)
		redir->type = APPEND;
	else if (ft_strncmp(tokens->literal, "<", 1) == 0)
		redir->type = REDIN;
	else if (ft_strncmp(tokens->literal, "<<", 2) == 0)
		redir->type = HEREDOC;
	redir->filename = ft_strdup(tokens->next->literal);
	redir->next = NULL;
	return (redir);
}

int	check_split(char *literal)
{
	int		i;
	int		check;
	char	quote;

	i = 0;
	check = LIE;
	while (literal[i] && literal[i] != ' ')
	{
		if (literal[i] == '"' || literal[i] == '\'')
		{
			check = TRUTH;
			quote = literal[i++];
			while (literal[i] && literal[i] != quote && literal[i + 1] != '\0')
				i++;
			if (literal[i])
				i++;
			break ;
		}
		i++;
	}
	if (literal[i] == ' ')
		return (i);
	return (LIE);
}
