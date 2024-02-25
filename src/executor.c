/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:05:13 by iusantos          #+#    #+#             */
/*   Updated: 2024/02/24 16:08:26 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	executor(t_meta *meta)
{
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
	run_first_pipeline_cmd(ast, pipe_fd, meta);
	ast = ast->right;
	while (ast)
	{
		if (ast->right == NULL)
			break ;
		run_middle_pipeline_cmd(ast, pipe_fd, meta);
		ast = ast->right;
	}
	run_last_pipeline_cmd(ast, pipe_fd, meta);
	free(pipe_fd);
	while(cap_n_upd_exit_status(meta) != -1);
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
