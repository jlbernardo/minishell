/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:05:13 by iusantos          #+#    #+#             */
/*   Updated: 2024/02/28 18:59:55 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	executor(t_meta *meta)
{
	execute_heredocs(meta->ast, meta);
	if (meta->ast->right == NULL)
		run_simple_command(meta->ast->left, meta);
	else
		run_pipeline(meta->ast, meta);
}

void	run_pipeline(t_ast *ast, t_meta *meta)
{
	int	*pipe_fd;

	pipe_fd = malloc(2 * sizeof(int));
	if (pipe(pipe_fd) == -1)
		return ;
	first_pipeline_cmd(ast, pipe_fd, meta);
	ast = ast->right;
	while (ast)
	{
		if (ast->right == NULL)
			break ;
		middle_pipeline_cmd(ast, pipe_fd, meta);
		ast = ast->right;
	}
	last_pipeline_cmd(ast, pipe_fd, meta);
	free(pipe_fd);
	while (handle_exit_status(meta) != -1)
		;
}

void	run_executable(t_cmd *data, t_meta *meta)
{
	int			exec_return;
	char		**argv;
	struct stat	buf;

	stat(data->pathname, &buf);
	if (S_ISDIR(buf.st_mode))
		path_error(meta, data->pathname, "Is a directory", 126);
	if (access(data->pathname, F_OK))
		path_error(meta, data->pathname, "No such file or directory", 127);
	if (access(data->pathname, X_OK))
		path_error(meta, data->pathname, "Permission denied", 126);
	argv = stringfy(data->word_list);
	exec_return = execve(data->pathname, argv, NULL);
	if (exec_return == -1)
	{
		perror(strerror(errno));
		free_str_array(argv, get_size(data->word_list));
		free(argv);
		finisher(*meta, "ATHE", errno);
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
		add_upd_hashtable("?", exit_str, meta->hash);
	free(exit_str);
	return (exit_code);
}

void	exec_forked_command(t_cmd *data, t_meta *meta)
{
	int	exit_code;

	if (is_builtin(data->word_list[0].word))
	{
		exit_code = run_builtin(meta, data->word_list);
		close_all_fds();
		finisher(*meta, "ATHE", exit_code);
	}
	else if (data->pathname == NULL)
	{
		handle_null_pathname(data->word_list->word, meta);
		close_all_fds();
		finisher(*meta, "ATHE", 127);
	}
	else
		run_executable(data, meta);
}
