/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:38:30 by julberna          #+#    #+#             */
/*   Updated: 2024/01/23 14:34:56 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	t_token	*tokens;
	t_ast_node	*ast;

	lexer(&tokens);
	ast = parse_pipeline(&tokens, NULL);
	// test freeing of word_lists
	// free_wl2(ast->left->data->word_list);
	// test freewing of redirect list
	// free_redirects2(ast->left->data->redirects);
	printf("%p", ast);
	return (0);
}
