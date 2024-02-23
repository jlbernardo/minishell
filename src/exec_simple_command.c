/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:42:52 by iusantos          #+#    #+#             */
/*   Updated: 2024/02/23 16:05:12 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	run_simple_command(t_ast *cmd_node, t_meta *meta)
{
	pid_t	child_pid;
	int		exit_status;

	if (is_builtin(cmd_node->data->word_list[0].word))
		run_builtin(meta, cmd_node->data->word_list);
	else
	{
		if (cmd_node->data->pathname == NULL)
			handle_null_pathname(meta);
		else
		{
			if ((child_pid = fork()) == -1)
				return ;
			if (child_pid == 0)
				run_executable(cmd_node->data, meta);
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
		add_or_upd_ht_entry("?", "126", meta->hash);
		return ;
	}
	exit_string = ft_itoa(WEXITSTATUS(exit_status));
	add_or_upd_ht_entry("?", exit_string, meta->hash);
	free(exit_string);
}

void	handle_null_pathname(t_meta *meta)
{
	ft_putstr_fd("minishell: command not found\n", 2);
	add_or_upd_ht_entry("?", "127", meta->hash);
}
