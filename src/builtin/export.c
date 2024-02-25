/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:52:24 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/24 18:54:47 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_alone(t_hash **ht);
void	export_error(char *literal, int *ret);
void	without_value(t_word *wl, t_hash **ht);
void	with_value(t_word *wl, t_hash **ht, int *ret);

int	export(t_meta *meta, t_word *wl)
{
	int			ret;
	t_word		*temp;

	ret = EXIT_SUCCESS;
	temp = wl;
	temp = temp->next;
	if (temp)
	{
		while (temp)
		{
			if (valid_variable(temp->word) && ft_strchr(temp->word, '='))
				with_value(temp, meta->hash, &ret);
			else if (valid_variable(temp->word))
				without_value(temp, meta->hash);
			else
				export_error(temp->word, &ret);
			temp = temp->next;
		}
	}
	else
		export_alone(meta->hash);
	return (ret);
}

void	with_value(t_word *wl, t_hash **ht, int *ret)
{
	int			len;
	char		*name;
	char		*value;
	char		*pre_value;

	len = ft_strchr(wl->word, '=') - wl->word;
	name = ft_substr(wl->word, 0, len);
	len = ft_strlen(wl->word) - len - 1;
	pre_value = ft_substr(ft_strchr(wl->word, '='), 1, len);
	value = ft_strtrim(pre_value, "\"'");
	if (is_readonly(name))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(name, STDERR_FILENO);
		ft_putendl_fd(": readonly variable", STDERR_FILENO);
		*ret = EXIT_FAILURE;
	}
	else
		add_or_upd_ht_entry(name, value, ht);
	free(name);
	free(value);
	free(pre_value);
}

void	without_value(t_word*wl, t_hash **ht)
{
	char	*value;

	if (is_readonly(wl->word))
		return ;
	value = grab_value(wl->word, ht);
	if (!value)
		add_or_upd_ht_entry(wl->word, NULL, ht);
	free(value);
}

void	export_error(char *literal, int *ret)
{
	ft_putstr_fd("minishell: export: '", STDERR_FILENO);
	ft_putstr_fd(literal, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	*ret = EXIT_FAILURE;
}

void	export_alone(t_hash **ht)
{
	t_word	*vars;

	vars = NULL;
	populate_sort_vars(ht, &vars);
	sort_vars(&vars, vars, NULL);
	print_export(vars, ht);
	free_wl(vars);
	free(vars);
}
