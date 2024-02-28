/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:31:26 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/27 17:53:46 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

unsigned int	hash(char *name)
{
	unsigned int	i;
	unsigned int	size;
	unsigned int	hash_value;

	hash_value = 0;
	size = ft_strlen(name);
	i = 0;
	while (i < size)
	{
		hash_value = hash_value * 37 + name[i];
		i++;
	}
	hash_value = hash_value % HT_SIZE;
	return (hash_value);
}

t_hash	*create_kv_pair(char *name, char *value)
{
	t_hash	*kv_pair;

	kv_pair = ft_calloc(1, sizeof(t_hash));
	if (kv_pair == NULL)
		return (NULL);
	kv_pair->name = ft_strdup(name);
	if (value)
		kv_pair->value = ft_strdup(value);
	else
		kv_pair->value = NULL;
	kv_pair->next = NULL;
	return (kv_pair);
}

void	add_upd_hashtable(char *name, char *value, t_hash **ht)
{
	t_hash			**entry;
	t_hash			**prev;
	unsigned int	index;

	index = hash(name);
	entry = &ht[index];
	if (*entry == NULL)
	{
		*entry = create_kv_pair(name, value);
		return ;
	}
	while (*entry != NULL)
	{
		if (ft_strcmp((*entry)->name, name) == 0)
		{
			free((*entry)->value);
			(*entry)->value = ft_strdup(value);
			return ;
		}
		prev = entry;
		entry = &(*prev)->next;
	}
	(*prev)->next = create_kv_pair(name, value);
}

char	*grab_value(char *name, t_hash **ht)
{
	t_hash			*entry;
	t_hash			*prev;
	unsigned int	index;

	index = hash(name);
	entry = ht[index];
	while (entry != NULL)
	{
		if (ft_strcmp(entry->name, name) == 0)
		{
			if (entry->value)
				return (ft_strdup(entry->value));
			break ;
		}
		prev = entry;
		entry = prev->next;
	}
	return (NULL);
}

int	last_exit(t_meta *meta)
{
	int		exit_code;
	char	*exit_str;

	exit_str = grab_value("?", meta->hash);
	exit_code = ft_atoi(exit_str);
	free(exit_str);
	return (exit_code);
}
