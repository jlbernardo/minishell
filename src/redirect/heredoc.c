/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:56:18 by iusantos          #+#    #+#             */
/*   Updated: 2024/03/04 14:53:01 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_heredocs(t_ast *ast, t_meta *meta)
{
	int		child_pid;
	int		exit_status;

	child_pid = fork();
	heredoc_signal(child_pid);
	if (child_pid == 0)
		child_heredoc(meta, ast);
	waitpid(-1, &exit_status, 0);
	basic_signal(meta);
	if (WEXITSTATUS(exit_status) == 1)
	{
		add_upd_hashtable("?", "130", meta->hash);
		meta->ast->success = LIE;
		return (LIE);
	}
	return (TRUTH);
}

void	child_heredoc(t_meta *meta, t_ast *ast)
{
	while (ast)
	{
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

void	capture_content(t_redir *rl, t_meta *meta)
{
	int				heredoc_fd;
	char			*tmp_file;
	static int		cmd_nbr;

	while (rl != NULL)
	{
		if (rl->type == HEREDOC)
		{
			tmp_file = gen_tmpfile_name(cmd_nbr);
			heredoc_fd = open(tmp_file, O_CREAT | O_RDWR | O_TRUNC, 0666);
			free(tmp_file);
			fill_tmpfile(heredoc_fd, rl, meta);
		}
		rl = rl->next;
	}
	cmd_nbr++;
}

void	fill_tmpfile(int fd, t_redir *r, t_meta *meta)
{
	char			*input;
	unsigned int	size;

	input = readline("> ");
	if (signal_received(input, r, fd, meta) == 1)
		return ;
	while (ft_strcmp(input, r->filename) != 0)
	{
		size = ft_strlen(input);
		if (size == 0)
			write(fd, "\n", 1);
		else
			expand_and_write(&input, fd, meta);
		free(input);
		input = readline("> ");
		if (signal_received(input, r, fd, meta) == 1)
			return ;
		if (ft_strcmp(input, r->filename) == 0)
		{
			free(input);
			write_and_close(fd);
			break ;
		}
		write(fd, "\n", 1);
	}
}
