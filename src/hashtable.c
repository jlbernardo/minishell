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
		i++;
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
	t_ht_entry		**entry;
	t_ht_entry		**prev;

	index = hash(name);
	entry = &ht[index];
	if (*entry == NULL)
	{
		*entry = create_kv_pair(name, value);
		return;
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

char	*grab_value(char *name, t_ht_entry **ht)
{
	unsigned int	index;
	t_ht_entry		*entry;
	t_ht_entry		*prev;

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

void	add_env_to_ht(char **env, t_ht_entry **ht)
{
	char **pair;

	while (*env)
	{
		pair = ft_split(*env, '=');
		add_or_upd_ht_entry(pair[0], pair[1], ht);
		safe_free(pair[0]);
		safe_free(pair[1]);
		safe_free(pair);
		env++;
	}
}

void	safe_free(void *p)
{
	if (p == NULL)
		return ;
	free(p);
	p = NULL;
}

void	free_ht(t_ht_entry **ht)
{
	unsigned int i;

	i = 0;
	while (i < HT_SIZE)
	{
		if (ht[i] != NULL)
			free_ht_entry(ht[i]);
		i++;
	}
	safe_free(ht);
}

void	free_ht_entry(t_ht_entry	*ht)
{
	if (ht->next != NULL)
		free_ht_entry(ht->next);
	safe_free(ht->name);
	safe_free(ht->value);
	safe_free(ht);
}
