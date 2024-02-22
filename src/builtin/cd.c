/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:11:53 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/22 15:12:53 by Juliany Ber      ###   ########.fr       */
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

	path = set_path(wl->next, meta->hash);
	ret = chdir(path);
	len = get_size(wl);
	if (ret == -1 || len > 2)
		ret = give_error(path, len);
	else
	{
		old_cwd = grab_value("PWD", meta->hash);
		cwd = getcwd(NULL, PATH_MAX);
		add_or_upd_ht_entry("PWD", cwd, meta->hash);
		add_or_upd_ht_entry("OLDPWD", old_cwd, meta->hash);
		free(cwd);
		free(old_cwd);
	}
	free(path);
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
		ft_putendl_fd("minishell: cd: too many arguments", 2);
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
