/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:38:49 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/24 16:47:43 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	get_path(t_ast **ast, t_hash **hash)
{
	int		i;
	char	**paths;
	char	*full_path;

	if (!*ast)
		return ;
	if ((*ast)->type == CMD && !is_builtin((*ast)->data->word_list->word))
	{
		if (ft_strchr((*ast)->data->word_list->word, '/'))
			(*ast)->data->pathname = ft_strdup((*ast)->data->word_list->word);
		else
		{
			full_path = grab_value("PATH", hash);
			paths = ft_split(full_path, ':');
			find_path(ast, paths);
			free(full_path);
			i = -1;
			while (paths[++i] != NULL)
				free(paths[i]);
			free(paths);
		}
	}
	get_path(&(*ast)->left, hash);
	get_path(&(*ast)->right, hash);
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
