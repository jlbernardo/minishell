/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:11:53 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/20 18:04:23 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*set_error(char *path);
char	*set_path(t_token *node, t_hash **ht);

int	cd(t_token *tokens, t_hash **ht)
{
	int		ret;
	char	*cwd;
	char	*path;
	char	*old_cwd;
	char	*err_str;

	old_cwd = grab_value("PWD", ht);
	path = set_path(tokens->next, ht);
	err_str = set_error(path);
	ret = chdir(path);
	if (ret == -1)
		perror(err_str);
	else
	{
		cwd = getcwd(NULL, PATH_MAX);
		add_or_upd_ht_entry("PWD", cwd, ht);
		add_or_upd_ht_entry("OLDPWD", old_cwd, ht);
		free(cwd);
	}
	free(path);
	free(err_str);
	free(old_cwd);
	return (ret);
}

char	*set_path(t_token *node, t_hash **ht)
{
	if (node)
		return (ft_strdup(node->literal));
	else
		return (grab_value("HOME", ht));
}

char	*set_error(char *path)
{
	int		size;
	char	*err_str;

	size = ft_strlen(path) + 11;
	err_str = ft_calloc(size, sizeof(char));
	ft_strlcat(err_str, "minishell: cd: ", size);
	ft_strlcat(err_str, path, size);
	return (err_str);
}
