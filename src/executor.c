/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:05:13 by iusantos          #+#    #+#             */
/*   Updated: 2024/02/23 21:06:59 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	executor(t_meta *meta)
{
	if (meta->ast->right == NULL)
		run_simple_command(meta->ast->left, meta);
	else
		run_pipeline(meta->ast, 0, meta);
}

void	run_pipeline(t_ast *ast, int in_fd, t_meta *meta)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return ;
	fork_maker(ast, in_fd, meta, pipe_fd);
	if (in_fd != 0)
		close(in_fd);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	while (cap_n_upd_exit_status(meta) != -1)
		;
	return ;
}

void	fork_maker(t_ast *ast, int in_fd, t_meta *meta, int pipe_fd[2])
{
	pid_t	child_pid;

	if (ast->right->type == CMD)
	{
		child_pid = fork();
		if (child_pid == 0)
			exec_left(ast->left->data, in_fd, pipe_fd, meta);
		child_pid = fork();
		if (child_pid == 0)
			exec_right(ast->right->data, pipe_fd, meta);
	}
	else
	{
		child_pid = fork();
		if (child_pid == 0)
			exec_left(ast->left->data, in_fd, pipe_fd, meta);
		close(pipe_fd[1]);
		run_pipeline(ast->right, pipe_fd[0], meta);
		close(pipe_fd[0]);
	}
}

void	run_executable(t_cmd *data, t_meta *meta)
{
	int		exec_return;
	char	**array_of_strings;

	array_of_strings = NULL;
	array_of_strings = stringfy(data->word_list);
	exec_return = execve(data->pathname, array_of_strings, NULL);
	if (exec_return == -1)
	{
		perror(strerror(errno));
		free_array_of_strings(array_of_strings, get_size(data->word_list));
		free(array_of_strings);
		finisher(*meta);
		free_ht(meta->hash);
		exit(errno);
	}
}

int	run_builtin(t_meta *meta, t_word *wl)
{
	int				i;
	int				exit_code;
	char			*exit_str;
	const t_builtin	builtin[] = {{"cd", cd}, {"echo", echo}, \
			{"env", env}, {"exit", ft_exit}, {"export", export}, \
			{"pwd", pwd}, {"unset", unset}};

	i = -1;
	exit_code = 0;
	exit_str = NULL;
	while (++i < 8)
	{
		if (ft_strcmp(builtin[i].cmd_name, wl->word) == 0)
		{
			exit_code = builtin[i].function(meta, wl);
			break ;
		}
	}
	exit_str = ft_itoa(exit_code);
	if (!exit_str)
		handle_null_pathname(wl->word, meta);
	else
		add_or_upd_ht_entry("?", exit_str, meta->hash);
	free(exit_str);
	return (exit_code);
}
