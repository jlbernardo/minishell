/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:12:03 by julberna          #+#    #+#             */
/*   Updated: 2024/02/29 21:30:22 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser(t_meta *meta)
{
	t_token	*temp;

	if (!meta->tokens)
	{
		add_upd_hashtable("?", "0", meta->hash);
		return (LIE);
	}
	remove_quotes(&meta->tokens, 0, 0, 0);
	remove_empty_tokens(&meta->tokens);
	temp = meta->tokens;
	meta->ast = parse_pipeline(&meta->tokens, NULL, meta);
	meta->tokens = temp;
	get_path(&meta->ast, meta->hash);
	execute_heredocs(meta->ast, meta);
	check_invalid_commands(meta->ast, meta);
	if (meta->ast && meta->ast->success)
		return (TRUTH);
	return (LIE);
}

void	remove_quotes(t_token **tokens, int i, int len, char quote)
{
	if (!*tokens)
		return ;
	if ((*tokens)->type == REDIRECT && ft_strcmp((*tokens)->literal, "<<") == 0)
	{
		remove_quotes(&(*tokens)->next->next, 0, 0, 0);
		return ;
	}
	while ((*tokens)->literal[i] != '\0')
	{
		if (((*tokens)->literal[i] == '"' || (*tokens)->literal[i] == '\''))
		{
			quote = (*tokens)->literal[i];
			if (i > 0 && ((*tokens)->literal[i - 1] == '='))
				break ;
			len = ft_strlen((*tokens)->literal) - i;
			ft_memmove(&(*tokens)->literal[i], &(*tokens)->literal[i + 1], len);
			while ((*tokens)->literal[i] != quote)
				i++;
			len = ft_strlen((*tokens)->literal) - i;
			ft_memmove(&(*tokens)->literal[i], &(*tokens)->literal[i + 1], len);
			continue ;
		}
		i++;
	}
	remove_quotes(&(*tokens)->next, 0, 0, 0);
}

void	remove_empty_tokens(t_token **tokens)
{
	t_token	*curr;

	curr = *tokens;
	if (!tokens || !*tokens)
		return ;
	if (!curr->literal)
	{
		*tokens = curr->next;
		free(curr->literal);
		free(curr);
		remove_empty_tokens(tokens);
	}
	else
		remove_empty_tokens(&curr->next);
}

void	check_invalid_commands(t_ast *ast, t_meta *meta)
{
	if (!ast)
		return ;
	if (ast->data && !ast->data->pathname
		&& !is_builtin(ast->data->word_list[0].word))
		handle_null_pathname(ast->data->word_list->word, meta);
	check_invalid_commands(ast->left, meta);
	check_invalid_commands(ast->right, meta);
}

t_redir	*new_redirect(t_token *tokens)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	if (ft_strncmp(tokens->literal, ">", 1) == 0)
		redir->type = REDOUT;
	else if (ft_strncmp(tokens->literal, ">>", 2) == 0)
		redir->type = APPEND;
	else if (ft_strncmp(tokens->literal, "<", 1) == 0)
		redir->type = REDIN;
	else if (ft_strncmp(tokens->literal, "<<", 2) == 0)
		redir->type = HEREDOC;
	redir->filename = ft_strdup(tokens->next->literal);
	redir->next = NULL;
	return (redir);
}
