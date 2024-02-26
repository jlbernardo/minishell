/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:42:52 by iusantos          #+#    #+#             */
<<<<<<< HEAD:src/exec_simple_command.c
/*   Updated: 2024/02/22 14:56:08 by iusantos         ###   ########.fr       */
=======
/*   Updated: 2024/02/25 00:07:00 by Juliany Ber      ###   ########.fr       */
>>>>>>> dev:src/executor/exec_simple_command.c
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_simple_command(t_ast *cmd, t_meta *meta)
{
	pid_t	child_pid;
	int		exit_status;

<<<<<<< HEAD:src/exec_simple_command.c
	//TODO: deal with redirects
	//execute_heredoc(cmd_node->data->redirects, meta);
	if (is_builtin(cmd_node->data->word_list[0].word))
		run_builtin(cmd_node->data->word_list);
=======
	if (is_builtin(cmd->data->word_list[0].word))
		run_builtin(meta, cmd->data->word_list);
>>>>>>> dev:src/executor/exec_simple_command.c
	else
	{
		if (cmd->data->pathname == NULL)
			handle_null_pathname(cmd->data->word_list->word, meta);
		else
		{
			child_pid = fork();
			if (child_pid == -1)
				return ;
			if (child_pid == 0)
				run_executable(cmd->data, meta);
			wait(&exit_status);
			upd_simple_exit_status(exit_status, meta);
		}
	}
}

void	upd_simple_exit_status(int exit_status, t_meta *meta)
{
	char	*exit_string;

	if (exit_status == 13)
	{
		add_upd_hashtable("?", "126", meta->hash);
		return ;
	}
	exit_string = ft_itoa(WEXITSTATUS(exit_status));
	add_upd_hashtable("?", exit_string, meta->hash);
	free(exit_string);
}
