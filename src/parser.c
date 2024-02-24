/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:12:03 by julberna          #+#    #+#             */
/*   Updated: 2024/02/24 00:59:33 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	split_tokens(t_meta *meta);

int	parser(t_meta *meta)
{
	t_token	*temp;

	if (!meta->tokens)
		return (LIE);
	expand_variables(&meta->tokens, meta);
	remove_quotes(&meta->tokens);
	split_tokens(meta);
	remove_empty_tokens(&meta->tokens);
	temp = meta->tokens;
	meta->ast = parse_pipeline(&meta->tokens, NULL);
	get_path(&meta->ast, meta->hash);
	meta->tokens = temp;
	if (meta->ast && meta->ast->success)
		return (TRUTH);
	return (LIE);
}

int	check_where_to_split(char *literal)
{
	int		i;
	int		check;
	char	quote;

	i = 0;
	check = LIE;
	while (literal[i] && literal[i] != ' ')
	{
		if (literal[i] == '"' || literal[i] == '\'')
		{
			check = TRUTH;
			quote = literal[i++];
			while (literal[i] != quote)
				i++;
			i++;
			break ;
		}
		i++;
	}
	if (literal[i] == ' ')
		return (i);
	return (LIE);
}

void	split_tokens(t_meta *meta)
{
	int		post_space;
	int		pre_space;
	char	*other_temp;
	char	*str_temp;
	t_token	*tk_next;
	t_token	*tk;

	tk = meta->tokens;
	while (tk)
	{
		if (check_where_to_split(tk->literal))
		{
			pre_space = ft_strchr(tk->literal, ' ') - tk->literal;
			post_space = ft_strlen(tk->literal) - pre_space - 1;
			str_temp = ft_strdup(tk->literal);
			free(tk->literal);
			tk->literal = ft_substr(str_temp, 0, pre_space);
			tk_next = tk->next;
			tk->next = NULL;
			other_temp = ft_substr(ft_strchr(str_temp, ' '), 1, post_space);
			new_token(&tk, WORD, other_temp);
			tk_last(tk)->next = tk_next;
			free(other_temp);
			free(str_temp);
			split_tokens(meta);
		}
		tk = tk->next;
	}
}

void	remove_empty_tokens(t_token **tokens)
{
	t_token	*curr;

	curr = *tokens;
	if (!tokens || !*tokens)
		return ;
	if (!curr->literal || ft_strlen(curr->literal) == 0)
	{
		*tokens = curr->next;
		free(curr->literal);
		free(curr);
		remove_empty_tokens(tokens);
	}
	else
		remove_empty_tokens(&curr->next);
}

void	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", \
		STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}
