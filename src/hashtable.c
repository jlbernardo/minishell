/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:31:26 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/07 16:18:10 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	kv_pair->value = ft_strdup(value);
	kv_pair->next = NULL;
	return (kv_pair);
}

void	add_or_upd_ht_entry(char *name, char *value, t_hash **ht)
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
			return (ft_strdup(entry->value));
		prev = entry;
		entry = prev->next;
	}
	return (NULL);
}

void	add_env_to_ht(char **env, t_hash **ht)
{
	char			*pair[2];
	unsigned int	len_after_equal;
	unsigned int	len_before_equal;

	while (*env)
	{
		len_before_equal = ft_strchr(*env, '=') - *env;
		len_after_equal = ft_strlen(*env) - len_before_equal - 1;
		pair[0] = ft_substr(*env, 0, len_before_equal);
		pair[1] = ft_substr(ft_strchr(*env, '='), 1, len_after_equal);
		add_or_upd_ht_entry(pair[0], pair[1], ht);
		safe_free(pair[0]);
		safe_free(pair[1]);
		env++;
	}
}
