/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:56:18 by iusantos          #+#    #+#             */
/*   Updated: 2024/02/22 18:31:10 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//percorre a arvore chamando capture content
int	execute_heredocs(t_ast *ast)
{
	capture_content(ast->left);
	if (ast->right == NULL)
		return (1);
	else
	{
		if (ast->right->type == CMD)
			capture_content(ast->right);
		else
			execute_heredocs(ast->right);
	}
	return 1;
}

void	capture_content(t_ast *node)
{

}
