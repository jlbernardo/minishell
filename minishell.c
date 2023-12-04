#include <stdio.h>
#include "includes/minishell.h"

int main(void)
{
	char *input;

	while (1)
	{
		input = readline("$>");
		printf("%s\n", input);
		free(input);
	}

	return (0);
}
