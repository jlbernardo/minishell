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
	token->next = NULL;
	return (token);
}

void	append_token(t_tk **head, t_tk *token)
{
	t_tk	*last;

	if (*head == NULL)
	{
		*head = token;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = token;
}

char *read_identifier(t_lexer *l)
{
	char *identifier;
	size_t len;

	while (ft_isalnum(l->input[l->read_pos]) || l->input[l->read_pos] == '_')
		++l->read_pos;
	len = l->read_pos - l->pos;
	identifier = ft_substr(l->input, l->pos, len);
	l->pos = l->read_pos - 1;
	return (identifier);
}

void	next_token(t_lexer *l, t_tk **head)
{
	char *ident;
	if (ft_isalpha(l->ch) || l->ch == '_')
	{
		append_token(head, new_token(IDENT, ident = read_identifier(l)));
		free(ident);
		return ;
	}
	if (l->ch == '(')
		return append_token(head, new_token(LPAREN, "("));
	if (l->ch == ')')
		return append_token(head, new_token(RPAREN, ")"));
	if (l->ch == ';')
		return append_token(head, new_token(SEMICOLON, ";"));
	if (l->ch == '|')
		return append_token(head, new_token(PIPE, "|"));
}

int main(void)
{
	t_tk **head;
	char *input;
	t_lexer	lexer;

	head = ft_calloc(1, sizeof(t_tk **));
	input = readline("$>");
	set_lexer(&lexer, input);
	while(lexer.read_pos <= lexer.size)
	{
		read_char(&lexer);
		next_token(&lexer, head);
	}
	free(input);

	return (0);
}
