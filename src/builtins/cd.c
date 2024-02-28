/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:11:53 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/28 17:35:36 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		give_error(char *path, int len);
char	*set_path(t_word *wl, t_hash **ht);

int	cd(t_meta *meta, t_word *wl)
{
	int		ret;
	int		len;
	char	*cwd;
	char	*path;
	char	*old_cwd;

	len = get_size(wl);
	if (len > 2)
		ret = give_error(NULL, len);
	else
	{
		path = set_path(wl->next, meta->hash);
		ret = chdir(path);
		if (ret == -1)
			ret = give_error(path, 0);
		old_cwd = grab_value("PWD", meta->hash);
		cwd = getcwd(NULL, PATH_MAX);
		add_upd_hashtable("PWD", cwd, meta->hash);
		add_upd_hashtable("OLDPWD", old_cwd, meta->hash);
		free(cwd);
		free(old_cwd);
		free(path);
	}
	return (ret);
}

char	*set_path(t_word *wl, t_hash **ht)
{
	if (wl)
		return (ft_strdup(wl->word));
	else
		return (grab_value("HOME", ht));
}

int	give_error(char *path, int len)
{
	int		size;
	char	*err_str;

	if (len > 2)
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
	else
	{
		size = ft_strlen(path) + 16;
		err_str = ft_calloc(size, sizeof(char));
		ft_strlcat(err_str, "minishell: cd: ", size);
		ft_strlcat(err_str, path, size);
		perror(err_str);
		free(err_str);
	}
	return (EXIT_FAILURE);
}
