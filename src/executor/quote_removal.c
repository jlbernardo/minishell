/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:27:16 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/03/03 17:29:32 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_quotes(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == CMD)
	{
		redir_quotes(&ast->data->redirects, 0, 0, 0);
		wordlist_quotes(&ast->data->word_list, 0, 0, 0);
	}
	remove_quotes(ast->left);
	remove_quotes(ast->right);
}

void	wordlist_quotes(t_word **wordlist, int i, int len, char quote)
{
	if (!*wordlist)
		return ;
	if (ft_strcmp((*wordlist)->word, "<<") == 0 && (*wordlist)->next != NULL)
	{
		wordlist_quotes(&(*wordlist)->next->next, 0, 0, 0);
		return ;
	}
	while ((*wordlist)->word[i] != '\0')
	{
		if (((*wordlist)->word[i] == '"' || (*wordlist)->word[i] == '\''))
		{
			quote = (*wordlist)->word[i];
			if (i > 0 && ((*wordlist)->word[i - 1] == '='))
				break ;
			len = ft_strlen((*wordlist)->word) - i;
			ft_memmove(&(*wordlist)->word[i], &(*wordlist)->word[i + 1], len);
			while ((*wordlist)->word[i] != quote)
				i++;
			len = ft_strlen((*wordlist)->word) - i;
			ft_memmove(&(*wordlist)->word[i], &(*wordlist)->word[i + 1], len);
			continue ;
		}
		i++;
	}
	wordlist_quotes(&(*wordlist)->next, 0, 0, 0);
}

void	redir_quotes(t_redir **redir, int i, int len, char quote)
{
	if (!*redir)
		return ;
	if (ft_strcmp((*redir)->filename, "<<") == 0 && (*redir)->next != NULL)
	{
		redir_quotes(&(*redir)->next->next, 0, 0, 0);
		return ;
	}
	while ((*redir)->filename[i] != '\0')
	{
		if (((*redir)->filename[i] == '"' || (*redir)->filename[i] == '\''))
		{
			quote = (*redir)->filename[i];
			if (i > 0 && ((*redir)->filename[i - 1] == '='))
				break ;
			len = ft_strlen((*redir)->filename) - i;
			ft_memmove(&(*redir)->filename[i], &(*redir)->filename[i + 1], len);
			while ((*redir)->filename[i] != quote)
				i++;
			len = ft_strlen((*redir)->filename) - i;
			ft_memmove(&(*redir)->filename[i], &(*redir)->filename[i + 1], len);
			continue ;
		}
		i++;
	}
	redir_quotes(&(*redir)->next, 0, 0, 0);
}
