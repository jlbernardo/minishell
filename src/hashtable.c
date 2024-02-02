#include "includes/minishell.h"

unsigned int	hash(char *name)
{
	unsigned int hash_value;
	unsigned int i;
	unsigned int size;

	hash_value = 0;
	size = ft_strlen(name);
	i = 0;
	while (i < size)
	{
		hash_value = hash_value * 37 + name[i]; 
	}
	hash_value = hash_value % HT_SIZE;
	return (hash_value);
}

t_ht_entry	*create_kv_pair(char *name, char *value)
{
	t_ht_entry	*kv_pair;

	kv_pair	= ft_calloc(1, sizeof(t_ht_entry));
	if (kv_pair == NULL)
		return (NULL);
	kv_pair->name = ft_strdup(name);
	kv_pair->value = ft_strdup(value);
	kv_pair->next = NULL;
	return (kv_pair);
}

void	add_or_upd_ht_entry(char *name, char *value, t_ht_entry **ht)
{
	unsigned int	index;
	t_ht_entry		*entry;
	t_ht_entry		*prev;

	index = hash(name);
	entry = ht[index];
	if (entry == NULL)
	{
		entry = create_kv_pair(name, value);
		return;
	}
	while (entry != NULL)
	{
		if (ft_strcmp(entry->name, name) == 0)
		{
			free(entry->value);
			entry->value = ft_strdup(value);
			return ;
		}
		prev = entry;
		entry = prev->next;
	}
	prev->next = create_kv_pair(name, value);
}
