/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:38:49 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/21 21:12:39 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	get_path(t_ast **ast, t_hash **env_vars)
{
	int		i;
	char	**paths;
	char	*full_path;

	if (!*ast)
		return ;
	if ((*ast)->type == CMD && not_builtin((*ast)->data->word_list->word))
	{
		if (ft_strchr((*ast)->data->word_list->word, '/'))
			(*ast)->data->pathname = ft_strdup((*ast)->data->word_list->word);
		else
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
		if (access(try, F_OK) == 0)
		{
			(*ast)->data->pathname = try;
			break ;
		}
		free(try);
		i++;
	}
}

int	not_builtin(char *cmd)
{
	int					i;
	static const char	*builtins[7] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
	};

	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(cmd, builtins[i]))
			return (0);
		i++;
	}
	return (1);
}
