/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:52:24 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/20 20:21:24 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_alone(t_hash **ht);
void	export_error(char *literal, int *ret);
void	without_value(t_token *tokens, t_hash **ht);
void	with_value(t_token *tokens, t_hash **ht, int *ret);

int	export(t_token *tk, t_hash **ht)
{
	int			ret;

	ret = EXIT_SUCCESS;
	tk = tk->next;
	if (tk)
	{
		while (tk)
		{
			if (valid_variable(tk->literal) && ft_strchr(tk->literal, '='))
				with_value(tk, ht, &ret);
			else if (valid_variable(tk->literal))
				without_value(tk, ht);
			else
				export_error(tk->literal, &ret);
			tk = tk->next;
		}
	}
	else
		export_alone(ht);
	return (ret);
}

void	with_value(t_token *tokens, t_hash **ht, int *ret)
{
	int			len;
	char		*name;
	char		*value;
	const char	*read_only[7] = {"BASHOPTS", "BASH_VERSINFO", "EUID",
		"PPID", "SHELLOPTS", "UID", NULL};

	len = ft_strchr(tokens->literal, '=') - tokens->literal;
	name = ft_substr(tokens->literal, 0, len);
	len = ft_strlen(tokens->literal) - len - 1;
	value = ft_substr(ft_strchr(tokens->literal, '='), 1, len);
	len = -1;
	while (read_only[++len])
	{
		if (ft_strcmp(read_only[len], tokens->literal) == 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tokens->literal, 2);
			ft_putendl_fd(": readonly variable", 2);
			*ret = EXIT_FAILURE;
		}
	}
	if (len > 5)
		add_or_upd_ht_entry(name, value, ht);
	free(name);
	free(value);
}

void	without_value(t_token *tokens, t_hash **ht)
{
	char	*value;

	value = grab_value(tokens->literal, ht);
	if (!value)
		add_or_upd_ht_entry(tokens->literal, NULL, ht);
	free(value);
}

void	export_error(char *literal, int *ret)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(literal, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	*ret = EXIT_FAILURE;
}

void	export_alone(t_hash **ht)
{
	t_word	*vars;

	vars = NULL;
	populate_sort_vars(ht, &vars);
	sort_vars(&vars, vars, NULL);
	print_export(vars, ht);
	free_wl2(vars);
}
