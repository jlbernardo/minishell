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
