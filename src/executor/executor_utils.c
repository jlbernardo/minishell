/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:09:16 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/28 18:58:08 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**stringfy(t_word *word_list)
{
	int		size;
	int		index;
	char	**array;

	size = get_size(word_list) + 1;
	array = ft_calloc(size, sizeof(char *));
	index = 0;
	while (word_list->next != NULL)
	{
		array[index] = ft_strdup(word_list->word);
		index++;
		word_list = word_list->next;
	}
	array[index] = ft_strdup(word_list->word);
	return (array);
}

int	get_size(t_word *wl)
{
	int	len;

	len = 1;
	while (wl->next != NULL)
	{
		len++;
		wl = wl->next;
	}
	return (len);
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

int	handle_exit_status(t_meta *meta)
{
	int				exit_status;
	char			*exit_string;
	pid_t			current_child_pid;
	static pid_t	last_child_pid;

	current_child_pid = wait(&exit_status);
	if (current_child_pid > last_child_pid)
	{
		exit_status = WEXITSTATUS(exit_status);
		if (exit_status == 13)
			exit_string = ft_itoa(126);
		else
			exit_string = ft_itoa(exit_status);
		add_upd_hashtable("?", exit_string, meta->hash);
		free(exit_string);
	}
	last_child_pid = current_child_pid;
	return (current_child_pid);
}
