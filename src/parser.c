/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:55:58 by iusantos          #+#    #+#             */
/*   Updated: 2024/02/08 20:33:01 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	parser(t_token *tokens, t_ast **ast, t_hash **env_vars)
{
	expand_variables(&tokens, env_vars);
	remove_quotes(&tokens);
	*ast = parse_pipeline(&tokens, NULL);
	get_path(ast, env_vars);
}

t_ast	*parse_pipeline(t_token **tokens, t_ast *parent)
{
	t_ast	*pl_node;

	set_pl(&pl_node, &parent, tokens);
	if (!pl_node)
		return (NULL);
	pl_node->left = parse_cmd(tokens, pl_node);
	if (pl_node->left == NULL)
		return (NULL);
	if (*tokens == NULL)
		return (pl_node);
	else if (!ft_strncmp((*tokens)->literal, "|", 1) && has_other_pipes(*tokens)
		&& ft_strncmp((*tokens)->next->literal, "|", 1))
	{
		*tokens = (*tokens)->next;
		pl_node->right = parse_pipeline(tokens, pl_node);
	}
	else if (!ft_strncmp((*tokens)->literal, "|", 1)
		&& !has_other_pipes(*tokens) && (*tokens)->next != NULL)
	{
		*tokens = (*tokens)->next;
		pl_node->right = parse_cmd(tokens, pl_node);
	}
	else
		ft_printf("Syntax error near token %s\n", (*tokens)->literal);
	return (pl_node);
}

t_ast	*parse_cmd(t_token **tokens, t_ast *parent)
{
	t_ast	*cmd_node;

	set_cmd(&cmd_node, &parent);
	while (*tokens != NULL && ft_strncmp((*tokens)->literal, "|", 1))
	{
		if ((*tokens)->type == REDIRECT && (*tokens)->next->type == WORD)
		{
			append_redirect(new_redirect(*tokens), &cmd_node->data->redirects);
			*tokens = (*tokens)->next->next;
		}
		else if ((*tokens)->type == WORD)
		{
			append_wle(new_wle((*tokens)->literal), &cmd_node->data->word_list);
			*tokens = (*tokens)->next;
		}
		else
		{
			ft_printf("Syntax error near token %s\n", (*tokens)->literal);
			free_data(cmd_node->data);
			free(cmd_node);
			return (NULL);
		}
	}
	return (cmd_node);
}

void	get_path(t_ast **ast, t_hash **env_vars)
{
	int		i;
	char	**paths;
	char	*full_path;

	if (!*ast)
		return ;
	if ((*ast)->type == CMD)
	{
		full_path = grab_value("PATH", env_vars);
		paths = ft_split(full_path, ':');
		find_path(ast, paths);
		free(full_path);
		i = -1;
		while (paths[++i] != NULL)
			free(paths[i]);
		free(paths);
	}
	get_path(&(*ast)->left, env_vars);
	get_path(&(*ast)->right, env_vars);
}

void	find_path(t_ast **ast, char **paths)
{
	int		i;
	char	*try;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		try = ft_strjoin(temp, (*ast)->data->word_list->word);
		free(temp);
		if (access(try, X_OK) == 0)
		{
			(*ast)->data->pathname = try;
			break ;
		}
		free(try);
		i++;
	}
}
