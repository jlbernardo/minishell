/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:09:16 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/03/05 18:35:55 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	format_argv(t_word *word_list, char ***array)
{
	int		size;
	int		index;

	size = get_wl_size(word_list) + 1;
	*array = ft_calloc(size, sizeof(char *));
	index = 0;
	while (word_list->next != NULL)
	{
		(*array)[index] = ft_strdup(word_list->word);
		index++;
		word_list = word_list->next;
	}
	(*array)[index] = ft_strdup(word_list->word);
}

void	format_envp(t_hash **hash, char ***array)
{
	int		i;
	int		len;
	int		index;
	t_hash	*temp;

	i = -1;
	index = 0;
	*array = ft_calloc(get_envp_size(hash) + 1, sizeof(char *));
	while (++i < HT_SIZE)
	{
		temp = hash[i];
		while (hash[i])
		{
			if (hash[i]->value)
			{
				len = ft_strlen(hash[i]->name) + ft_strlen(hash[i]->value) + 2;
				(*array)[index] = ft_calloc(len, sizeof(char));
				ft_strlcat((*array)[index], hash[i]->name, len);
				ft_strlcat((*array)[index], "=", len);
				ft_strlcat((*array)[index++], hash[i]->value, len);
			}
			hash[i] = hash[i]->next;
		}
		hash[i] = temp;
	}
}

int	get_envp_size(t_hash **hash)
{
	int		i;
	int		len;
	t_hash	*temp;

	i = 0;
	len = 0;
	while (i < HT_SIZE)
	{
		temp = hash[i];
		while (hash[i])
		{
			len++;
			hash[i] = hash[i]->next;
		}
		hash[i] = temp;
		i++;
	}
	return (len);
}

int	get_wl_size(t_word *word_list)
{
	int	len;

	len = 1;
	while (word_list->next != NULL)
	{
		len++;
		word_list = word_list->next;
	}
	return (len);
}

int	exit_status(t_meta *meta, int exit_status, char *exit_str)
{
	pid_t			current_child_pid;
	static pid_t	last_child_pid;

	current_child_pid = wait(&exit_status);
	if (current_child_pid > last_child_pid)
	{
		if (WIFSIGNALED(exit_status) != 0)
		{
			exit_str = ft_itoa(128 + WTERMSIG(exit_status));
			add_upd_hashtable("?", exit_str, meta->hash);
			free(exit_str);
		}
		else if (WEXITSTATUS(exit_status) == 13)
			add_upd_hashtable("?", "126", meta->hash);
		else
		{
			exit_str = ft_itoa(WEXITSTATUS(exit_status));
			add_upd_hashtable("?", exit_str, meta->hash);
			free(exit_str);
		}
	}
	last_child_pid = current_child_pid;
	return (current_child_pid);
}
