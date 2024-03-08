/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:38:49 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/03/08 16:37:34 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_paths(char *full_path, char **paths);

void	get_path(t_ast **ast, t_hash **hash)
{
	char	**paths;
	char	*full_path;

	if (!*ast)
		return ;
	if ((*ast)->type == CMD && (*ast)->data->word_list
		&& !is_builtin((*ast)->data->word_list->word)
		&& ft_strlen((*ast)->data->word_list->word) > 0)
	{
		if (ft_strchr((*ast)->data->word_list->word, '/'))
			(*ast)->data->pathname = ft_strdup((*ast)->data->word_list->word);
		else
		{
			full_path = grab_value("PATH", hash);
			if (!full_path)
				return ;
			paths = ft_split(full_path, ':');
			find_path(ast, paths);
			free_paths(full_path, paths);
		}
	}
	get_path(&(*ast)->left, hash);
	get_path(&(*ast)->right, hash);
}

void	free_paths(char *full_path, char **paths)
{
	int	i;

	i = -1;
	free(full_path);
	while (paths[++i] != NULL)
		free(paths[i]);
	free(paths);
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
		if (access(try, F_OK) == 0)
		{
			(*ast)->data->pathname = try;
			break ;
		}
		free(try);
		i++;
	}
}
