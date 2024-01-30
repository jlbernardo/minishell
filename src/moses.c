/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moses.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:49:32 by julberna          #+#    #+#             */
/*   Updated: 2024/01/29 19:22:54 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// void	finisher(t_token **tokens, t_ast_node **ast)
// {
// 	free_ast(ast);
// }

//it's possible to rewrite this function with recursion -> see free_wl2
// void	free_wl(t_wl_element **wl)
// {
// 	t_wl_element	*next_word;

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

void	free_wl2(t_wl_element **wl)
{
	if (wl == NULL || *wl == NULL)
		return ;
	free_wl2(&(*wl)->next);
	free((*wl)->word);
	free(*wl);
}

//for recursive implementation see free_redirects2 below
// void	free_redirects(t_redirect **rl)
// {
// 	t_redirect	*next_redirect;

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

void	free_redirects2(t_redirect **rl)
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

void	free_ast(t_ast_node *ast)
{
	if (ast == NULL)
		return ;
	free_ast(ast->right);
	free_ast(ast->left);
	if (ast->type == CMD)
		free_data(ast->data);
	free(ast);
}
