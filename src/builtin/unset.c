/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:16:16 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/20 18:07:32 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_ht_entry(char *key, t_hash **ht);

int	unset(t_token *tokens, t_hash **ht)
{
	int			i;
	int			ret;
	const char	*read_only[7] = {"BASHOPTS", "BASH_VERSINFO", "EUID",
		"PPID", "SHELLOPTS", "UID", NULL};

	ret = EXIT_SUCCESS;
	tokens = tokens->next;
	while (tokens)
	{
		i = -1;
		while (read_only[++i])
		{
			if (ft_strcmp(read_only[i], tokens->literal) == 0)
			{
				ft_putstr_fd("minishell: unset: ", 2);
				ft_putstr_fd(tokens->literal, 2);
				ft_putendl_fd(": cannot unset: readonly variable", 2);
				ret = EXIT_FAILURE;
				break ;
			}
		}
		delete_ht_entry(tokens->literal, ht);
		tokens = tokens->next;
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
