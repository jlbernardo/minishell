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

unsigned int	check_builtin(char *word)
{
	if (!ft_strncmp(word, "echo", ft_strlen(word)) ||
		!ft_strncmp(word, "cd", ft_strlen(word)) ||
		!ft_strncmp(word, "pwd", ft_strlen(word)) ||
		!ft_strncmp(word, "export", ft_strlen(word)) ||
		!ft_strncmp(word, "unset", ft_strlen(word)) ||
		!ft_strncmp(word, "env", ft_strlen(word)) ||
		!ft_strncmp(word, "exit", ft_strlen(word)))
		return (1);
	return (0);
}

void	next_token(t_lexer *l, t_tk **head)
{
	char *word;
	if (ft_isalpha(l->ch) || l->ch == '_')
	{
		word = read_identifier(l);
		if (check_builtin(word))
			append_token(head, new_token(BUILTIN, word));
		else
			append_token(head, new_token(IDENT, word));
		free(word);
		return ;
	}
	else if (l->ch == '>')
	{
		//checa se o próximo é '>'
		if (l->input[l->read_pos] == '>')
		{
			append_token(head, new_token(APPEND, ">>"));
			l->pos++;
			l->read_pos++;
			return ;
		}
		else
		{
			return append_token(head, new_token(REDOUT, ">"));
		}
	}
	else if (l->ch == '<')
	{
		if (l->input[l->read_pos] == '<')
		{
			append_token(head, new_token(HEREDOC, "<<"));
			l->pos++;
			l->read_pos++;
			return ;
		}
		else
		{
			return append_token(head, new_token(REDIN, "<"));
		}
	}
	else if (l->ch == '(')
		return append_token(head, new_token(LPAREN, "("));
	else if (l->ch == ')')
		return append_token(head, new_token(RPAREN, ")"));
	else if (l->ch == ';')
		return append_token(head, new_token(SEMICOLON, ";"));
	else if (l->ch == '|')
		return append_token(head, new_token(PIPE, "|"));
	else if (l->ch == '~')
		return append_token(head, new_token(TILDE, "~"));
	else if ((l->ch >= 7 && l->ch <= 13) || l->ch == 32)
		return ;
	else if (l->ch == 0)
		return append_token(head, new_token(END, ""));
	else if (l->ch == '-' && l->input[l->read_pos] == 'n')
	{
		append_token(head, new_token(FLAG, "-n"));
		l->pos++;
		l->read_pos++;
		return ;
	}
	else
		return append_token(head, new_token(ILLEGAL, "ILLEGAL"));
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
