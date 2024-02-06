/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moses_i.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:49:32 by julberna          #+#    #+#             */
/*   Updated: 2024/02/06 18:37:49 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_wl2(t_word **wl)
{
	if (wl == NULL || *wl == NULL)
		return ;
	free_wl2(&(*wl)->next);
	free((*wl)->word);
	free(*wl);
}

void	free_redirects2(t_redir **rl)
{
	if (rl == NULL || *rl == NULL)
		return ;
	free_redirects2(&(*rl)->next);
	free((*rl)->filename);
	free(*rl);
}

void	free_data(t_cmd	*cmd)
{
	if (cmd == NULL)
		return ;
	free(cmd->pathname);
	free_wl2(cmd->word_list);
	free(cmd->word_list);
	free_redirects2(cmd->redirects);
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
		free_data(ast->data);
	free(ast);
}

// void	finisher(t_token **tokens, t_ast **ast)
// {
// 	free_ast(ast);
// }

//it's possible to rewrite this function with recursion -> see free_wl2
// void	free_wl(t_word **wl)
// {
// 	t_word	*next_word;

// 	if (wl == NULL)
// 		return ;
// 	while ((*wl)->next != NULL)
// 	{
// 		next_word = (*wl)->next;
// 		free((*wl)->word);
// 		free(*wl);
// 		*wl = next_word;
// 	}
// 	free((*wl)->word);
// 	free(*wl);
// }

//for recursive implementation see free_redirects2 below
// void	free_redirects(t_redir **rl)
// {
// 	t_redir	*next_redirect;

// 	if (rl == NULL)
// 		return ;
// 	while ((*rl)->next != NULL)
// 	{
// 		next_redirect = (*rl)->next;
// 		free((*rl)->filename);
// 		free(*rl);
// 		*rl = next_redirect;
// 	}
// 	free((*rl)->filename);
// 	free(*rl);
// }