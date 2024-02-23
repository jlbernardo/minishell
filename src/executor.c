/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:05:13 by iusantos          #+#    #+#             */
/*   Updated: 2024/02/22 21:19:57 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	executor(t_meta *meta)
{
	run_pipeline(meta->ast, 0, meta);
}

void	run_pipeline(t_ast *ast, int in_fd, t_meta *meta)
{
	int		pipe_fd[2];
	int		test_fd[2];
	pid_t	child_pid;

	test_fd[0] = 42;
	test_fd[1] = 43;
	if (pipe(pipe_fd) == -1 || !ast)
		return ;
	if (ast->right && ast->right->type == CMD)
	{
		child_pid = fork();
		if (child_pid == 0)
			exec_left(ast->left->data, in_fd, pipe_fd, meta);
		child_pid = fork();
		if (child_pid == 0)
			exec_right(ast->right->data, pipe_fd, meta);
	}
	else if (ast->right && ast->right->type == PIPELINE)
	{
		child_pid = fork();
		if (child_pid == 0)
			exec_left(ast->left->data, in_fd, pipe_fd, meta);
		close(pipe_fd[1]);
		run_pipeline(ast->right, pipe_fd[0], meta);
		close(pipe_fd[0]);
	}
	else
	{
		child_pid = fork();
		if (child_pid == 0)
			exec_left(ast->left->data, in_fd, test_fd, meta);
	}
	if (in_fd != 0)
		close(in_fd);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	while (cap_n_upd_exit_status(meta) != -1)
		;
	return ;
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

void	free_array_of_strings(char **array, int size)
{
	int	index;

	if (array == NULL)
		return ;
	index = 0;
	while (index <= size)
	{
		free(array[index]);
		index++;
	}
}

char	**stringfy(t_word *wl)
{
	char	**array;
	int		size;
	int		index;

	size = get_size(wl) + 1;
	array = ft_calloc(size, sizeof(char *));
	index = 0;
	while (wl->next != NULL)
	{
		array[index] = ft_strdup(wl->word);
		index++;
		wl = wl->next;
	}
	array[index] = ft_strdup(wl->word);
	return (array);
}

int	get_size(t_word *wl)
{
	int	nelem;

	nelem = 1;
	while (wl->next != NULL)
	{
		nelem++;
		wl = wl->next;
	}
	return (nelem);
}

void	run_builtin(t_meta *meta, t_word *wl)
{
	int				i;
	int				exit_code;
	const t_builtin	builtin[] = {{"cd", cd}, {"echo", echo}, \
			{"env", env}, {"exit", ft_exit}, {"export", export}, \
			{"pwd", pwd}, {"unset", unset}};

	i = -1;
	exit_code = 127;
	while (++i < 8)
	{
		if (ft_strcmp(builtin[i].cmd_name, wl->word) == 0)
		{
			exit_code = builtin[i].function(meta, wl);
			break ;
		}
	}
	finisher(*meta);
	free_ht(meta->hash);
	close_all_fds();
	exit(exit_code);
}

void	close_all_fds(void)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		close(i);
		i++;
	}
}

void	handle_null_pathname(t_meta *meta)
{
	ft_putstr_fd("minishell: command not found\n", 2);
	add_or_upd_ht_entry("?", "127", meta->hash);
}
