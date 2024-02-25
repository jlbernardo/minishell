/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:09:16 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/24 23:46:43 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

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

void	exec_forked_command(t_cmd *data, t_meta *meta)
{
	int	exit_code;

	if (is_builtin(data->word_list[0].word))
	{
		exit_code = run_builtin(meta, data->word_list);
		close_all_fds();
		finisher(*meta);
		free_hash(meta->hash);
		exit(exit_code);
	}
	else if (data->pathname == NULL)
		handle_forked_null_pathname(data, meta);
	else
		run_executable(data, meta);
}

int	handle_exit_status(t_meta *meta)
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
			add_upd_hashtable("?", "126", meta->hash);
		else
			add_upd_hashtable("?", exit_string, meta->hash);
		free(exit_string);
	}
	last_child_pid = current_child_pid;
	return (current_child_pid);
}
