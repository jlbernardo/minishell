/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:33:55 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/29 20:14:14 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_heredoc(t_meta *meta, t_ast *ast)
{
	while (ast)
	{
		signal(SIGINT, heredoc_sigint_handler);
		capture_content(ast->left->data->redirects, meta);
		if (ast->right != NULL)
		{
			if (ast->right->type == CMD)
			{
				capture_content(ast->right->data->redirects, meta);
				break ;
			}
		}
		ast = ast->right;
	}
	finisher(*meta, "ATHE", EXIT_SUCCESS);
}

void	expand_and_write(char *input, int fd, t_meta *meta)
{
	expand_variable(&input, meta);
	write(fd, input, ft_strlen(input));
}

int	handle_eof(char *input, t_redir *r, int fd, t_meta *meta)
{
	if (g_received_signal == SIGINT)
	{
		close(fd);
		finisher(*meta, "ATHE", 1);
	}
	if (input == NULL)
	{
		write(fd, "\n", STDOUT_FILENO);
		close(fd);
		ft_putstr_fd("minishell: warning: here-document delimited by"
			"end-of-file(wanted `", STDERR_FILENO);
		ft_putstr_fd(r->filename, STDERR_FILENO);
		ft_putendl_fd("')", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	write_and_close(int fd)
{
	write(fd, "\n\0", 2);
	close(fd);
}
