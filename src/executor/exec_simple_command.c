/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:42:52 by iusantos          #+#    #+#             */
/*   Updated: 2024/03/04 01:31:52 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_simple_command(t_ast *cmd, t_meta *meta)
{
	pid_t	child_pid;
	int		exit_status;

	if (cmd->data->word_list && process_redirects(cmd->data->redirects, meta))
	{
		if (is_builtin(cmd->data->word_list[0].word))
			run_builtin(meta, cmd->data->word_list);
		else
		{
			if (cmd->data->pathname == NULL)
				handle_null_pathname(cmd->data->word_list->word, meta);
			else
			{
				child_pid = fork();
				mid_exec_signal(child_pid);
				if (child_pid == -1)
					return ;
				if (child_pid == 0)
					run_executable(cmd->data, meta);
				wait(&exit_status);
				upd_simple_exit_status(exit_status, meta);
			}
		}
	}
}

void	upd_simple_exit_status(int exit_status, t_meta *meta)
{
	char	*exit_string;

	if (WIFSIGNALED(exit_status) && exit_status == 2)
	{
		ft_putstr_fd("\n", STDIN_FILENO);
		add_upd_hashtable("?", "130", meta->hash);
	}
	else if (WIFSIGNALED(exit_status) && exit_status == 131)
	{
		ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		add_upd_hashtable("?", "131", meta->hash);
	}
	else if (WEXITSTATUS(exit_status) == 13)
		add_upd_hashtable("?", "126", meta->hash);
	else
	{
		exit_string = ft_itoa(WEXITSTATUS(exit_status));
		add_upd_hashtable("?", exit_string, meta->hash);
		free(exit_string);
	}
}
