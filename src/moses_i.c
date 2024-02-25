/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moses_i.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:49:32 by julberna          #+#    #+#             */
/*   Updated: 2024/02/24 23:46:13 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_wordlist(t_word *wl)
{
	if (wl == NULL)
		return ;
	free_wordlist(wl->next);
	free(wl->next);
	free(wl->word);
}

void	free_redirects(t_redir *rl)
{
	if (rl == NULL)
		return ;
	free_redirects(rl->next);
	free(rl->filename);
}

void	free_cmd(t_cmd	*cmd)
{
	if (cmd == NULL)
		return ;
	free(cmd->pathname);
	free_wordlist(cmd->word_list);
	free(cmd->word_list);
	free_redirects(cmd->redirects);
	free(cmd->redirects);
	free(cmd);
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->literal);
		free(temp);
	}
}

void	free_ast(t_ast *ast)
{
	if (ast == NULL)
		return ;
	free_ast(ast->right);
	free_ast(ast->left);
	if (ast->type == CMD)
		free_cmd(ast->data);
	free(ast);
}
