/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:38:30 by julberna          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/01/23 15:38:06 by julberna         ###   ########.fr       */
=======
/*   Updated: 2024/01/24 11:37:02 by iusantos         ###   ########.fr       */
>>>>>>> dev-iury-parser
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	t_token	*tokens;
	t_ast_node	*ast;

	lexer(&tokens);
	ast = parse_pipeline(&tokens, NULL);
	free_ast(ast);
	printf("%p", ast);
	return (0);
}
