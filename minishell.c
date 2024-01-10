/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:43:53 by julberna          #+#    #+#             */
/*   Updated: 2024/01/10 16:23:02 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

char *read_string(t_lexer *l)
{
	char	*string;
	char	quote;
	size_t	len;

	quote = l->ch;
	l->pos = l->read_pos++;
	while (l->input[l->read_pos] != quote && l->input[l->read_pos] != '\0')
		++l->read_pos;
	len = l->read_pos - l->pos;
	string = ft_substr(l->input, l->pos, len);
	l->pos = l->read_pos - 1;
	l->ch = l->input[l->read_pos];
	return (string);
}

char *read_word(t_lexer *l)
{
	char *identifier;
	size_t len;

	while (ft_notspace(l->input[l->read_pos]))
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

unsigned int	check_variable(char **word, t_lexer *l)
{
	int	i;

	i = 0;
	if (*word[i] == '$' && (ft_isalpha((*word)[i + 1]) || 
		(*word)[i + 1] == '_'))
	{
		// word = word + 2;
		i += 2;
		while ((*word)[i])
		{
			if (ft_isalnum((*word)[i]) || (*word)[i] == '_')
				i++;
			else
			{
				(*word)[i] = '\0';
				l->read_pos -= l->read_pos - (ft_strlen(*word));
				l->pos = l->read_pos - 1;
				l->ch = l->input[l->read_pos];
				break ;
			}
		}
		return (1);
	}
	return (0);
}

void	next_token(t_lexer *l, t_tk **head)
{
	char *word;
	if (l->ch == '"')
	{
		word = read_string(l);
		if (l->ch == '"')
		{
			append_token(head, new_token(STRING, word));
			l->pos = l->read_pos++;
		}
		else
			append_token(head, new_token(ILLEGAL, word));
		free(word);
		return ;
	}
	else if (l->ch == 39)
	{
		word = read_string(l);
		if (l->ch == 39)
		{
			append_token(head, new_token(STRING, word));
			l->pos = l->read_pos++;
		}
		else
			append_token(head, new_token(ILLEGAL, word));
		free(word);
		return ;
	}
	else if (l->ch == '>')
	{
		//checa se o próximo é '>'
		if (l->input[l->read_pos] == '>')
		{
			append_token(head, new_token(APPEND, ">>"));
			l->pos = l->read_pos++;
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
			l->pos = l->read_pos++;
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
	else if (ft_notspace(l->ch))
	{
		word = read_word(l);
		if (check_builtin(word))
			append_token(head, new_token(BUILTIN, word));
		else if (check_variable(&word, l))
			append_token(head, new_token(VAR, word + 1));
		else
			append_token(head, new_token(WORD, word));
		free(word);
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
