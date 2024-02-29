/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:36:19 by iusantos          #+#    #+#             */
/*   Updated: 2024/02/28 21:10:47 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	first_pipeline_cmd(t_ast *ast, int pipe_fd[2], t_meta *meta)
{
	pid_t	child_pid;

	child_pid = fork();
	forked_signal(child_pid);
	if (child_pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		free(pipe_fd);
		exec_forked_command(ast->left->data, meta);
	}
	close(pipe_fd[1]);
}

void	middle_pipeline_cmd(t_ast *ast, int *pipe_fd, t_meta *meta)
{
	pid_t	child_pid;
	int		in_fd;

	in_fd = pipe_fd[0];
	if (pipe(pipe_fd) == -1)
		return ;
	child_pid = fork();
	forked_signal(child_pid);
	if (child_pid == 0)
	{
		dup2(in_fd, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(in_fd);
		free(pipe_fd);
		exec_forked_command(ast->left->data, meta);
	}
	close(in_fd);
	close(pipe_fd[1]);
}

void	last_pipeline_cmd(t_ast *ast, int *pipe_fd, t_meta *meta)
{
	pid_t	child_pid;

	child_pid = fork();
	forked_signal(child_pid);
	if (child_pid == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		free(pipe_fd);
		exec_forked_command(ast->data, meta);
	}
	close(pipe_fd[0]);
}

void	exec_left(t_cmd *data, int in_fd, int pipe_fd[2], t_meta *meta)
{
	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		close(pipe_fd[0]);
	}
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	exec_forked_command(data, meta);
}

void	exec_right(t_cmd *data, int pipe_fd[2], t_meta *meta)
{
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exec_forked_command(data, meta);
}
