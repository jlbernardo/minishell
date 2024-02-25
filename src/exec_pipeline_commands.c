/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:36:19 by iusantos          #+#    #+#             */
/*   Updated: 2024/02/24 17:29:57 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

void	exec_forked_command(t_cmd *data, t_meta *meta)
{
	int	exit_code;

	if (is_builtin(data->word_list[0].word))
	{
		exit_code = run_builtin(meta, data->word_list);
		close_all_fds();
		finisher(*meta);
		free_ht(meta->hash);
		exit(exit_code);
	}
	else if (data->pathname == NULL)
		handle_forked_null_pathname(data, meta);
	else
		run_executable(data, meta);
}

int	cap_n_upd_exit_status(t_meta *meta)
{
	static pid_t	last_child_pid;
	pid_t			current_child_pid;
	int				exit_status;
	char			*exit_string;

	current_child_pid = wait(&exit_status);
	if (current_child_pid > last_child_pid)
	{
		exit_status = WEXITSTATUS(exit_status);
		exit_string = ft_itoa(exit_status);
		if (exit_status == 13)
			add_or_upd_ht_entry("?", "126", meta->hash);
		else
			add_or_upd_ht_entry("?", exit_string, meta->hash);
		free(exit_string);
	}
	last_child_pid = current_child_pid;
	return (current_child_pid);
}
