/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:16:16 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/03/03 19:06:23 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		unset_error(char *word, char *reason);
void	delete_ht_entry(char *key, t_hash **ht);

int	unset(t_meta *meta, t_word *wl)
{
	int			ret;

	ret = EXIT_SUCCESS;
	wl = wl->next;
	while (wl)
	{
		if (is_readonly(wl->word))
			ret = unset_error(wl->word, "cannot unset: readonly variable");
		else if (ft_strchr(wl->word, '=') || !valid_variable(wl->word))
			ret = unset_error(wl->word, "not a valid identifier");
		else
			delete_ht_entry(wl->word, meta->hash);
		wl = wl->next;
	}
	return (ret);
}

void	delete_ht_entry(char *key, t_hash **ht)
{
	unsigned int	index;
	t_hash			*prev;
	t_hash			*entry;

	index = hash(key);
	entry = ht[index];
	if (entry == NULL)
		return ;
	while (entry)
	{
		if (!ft_strcmp(entry->name, key))
		{
			if (entry == ht[index])
				ht[index] = ht[index]->next;
			else
				prev->next = entry->next;
			free(entry->name);
			free(entry->value);
			free(entry);
			return ;
		}
		prev = entry;
		entry = entry->next;
	}
}

int	is_readonly(char *literal)
{
	int			i;
	const char	*read_only[7] = {"BASHOPTS", "BASH_VERSINFO", "EUID",
		"PPID", "SHELLOPTS", "UID", NULL};

	i = 0;
	while (read_only[i])
	{
		if (ft_strcmp(read_only[i], literal) == 0)
			return (TRUTH);
		i++;
	}
	return (LIE);
}

int	unset_error(char *word, char *reason)
{
	ft_putstr_fd("minishell: unset: ", STDERR_FILENO);
	ft_putstr_fd(word, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(reason, STDERR_FILENO);
	return (EXIT_FAILURE);
}
