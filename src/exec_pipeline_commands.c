/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:36:19 by iusantos          #+#    #+#             */
/*   Updated: 2024/02/21 14:47:22 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	exec_left_node(t_cmd *data, int in_fd, int pipe_fd[2], t_meta *meta)
{
	//TODO: change run_executable to run_command(can be builtin or executable)
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

void	exec_right_node(t_cmd *data, int pipe_fd[2], t_meta *meta)
{
	//TODO: change run_executable to run_command(can be builtin or executable)
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exec_forked_command(data, meta);
}

void	exec_forked_command(t_cmd *data, t_meta *meta)
{
	if (is_builtin(data->word_list[0].word))
	{
		run_builtin(data->word_list);
		//collect exit_status
	}
	else
	{
		if (data->pathname == NULL)
		{
			//change to handle_forked_pathname
			handle_forked_null_pathname(meta);
			return ;
		}
		else
		{
			run_executable(data, meta);
		}
	}
}

void	handle_forked_null_pathname(t_meta *meta)
{
	ft_putstr_fd("Minishell: Command not found\n", 2);
	// add_or_upd_ht_entry("?", "127", meta->env_vars);
	finisher(meta->tokens, meta->ast);
	free_ht(meta->env_vars);
	close_all_fds();
	exit(127);
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
		{
			add_or_upd_ht_entry("?", "126", meta->env_vars);
		}
		else
		{
			add_or_upd_ht_entry("?", exit_string, meta->env_vars);
		}
		free(exit_string);
	}
	last_child_pid = current_child_pid;
	return (current_child_pid);
}

