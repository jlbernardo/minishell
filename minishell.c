#include <stdio.h>
#include "includes/minishell.h"

void	set_lexer(t_lexer *lexer, char *input)
{
	lexer->input = input;
	lexer->pos = 0;
	lexer->read_pos = 0;
	lexer->ch = 0;
	lexer->size = ft_strlen(input);
}

void	read_char(t_lexer *l)
{
	if (l->read_pos >= l->size)
		l->ch = 0;
	else
		l->ch = l->input[l->read_pos];
	l->pos = l->read_pos;
	l->read_pos++;
}

t_tk	*new_token(t_tk_type type, char *literal)
{
	t_tk *token;

	token = ft_calloc(1, sizeof(t_tk *));
	token->type = type;
	token->literal = ft_strdup(literal);
	return (token);
}

int main(void)
{
	char *input;
	t_lexer	lexer;

	input = readline("$>");
	set_lexer(&lexer, input);
	free(input);

	return (0);
}
