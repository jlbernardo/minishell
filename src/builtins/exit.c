/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:35:43 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/27 18:15:50 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		bigger_than_llmax(char *exit_code);
int		smaller_than_llmin(char *exit_code);
int		exit_error(char *literal, char *reason);
char	*trim_prefix(const char *s1, const char *set);

int	ft_exit(t_meta *meta, t_word *wl)
{
	char			*arg;
	long long int	exit_code;

	(void)wl;
	exit_code = last_exit(meta);
	ft_putendl_fd(meta->tokens->literal, STDOUT_FILENO);
	if (meta->tokens->next)
	{
		arg = meta->tokens->next->literal;
		if ((!ft_isdigit(*arg) && *arg != '-' && *arg != '+')
			|| bigger_than_llmax(arg) || smaller_than_llmin(arg))
			exit_code = exit_error(arg, "numeric argument required");
		else if (meta->tokens->next->next)
		{
			add_upd_hashtable("?", "1", meta->hash);
			return (exit_error(NULL, "too many arguments"));
		}
		else
			exit_code = ft_atol(arg);
	}
	finisher(*meta, "ATHE", exit_code);
	return (exit_code);
}

int	exit_error(char *literal, char *reason)
{
	int	exit_code;

	exit_code = 1;
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	if (literal)
	{
		ft_putstr_fd(literal, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		exit_code = 2;
	}
	ft_putendl_fd(reason, STDERR_FILENO);
	return (exit_code);
}

int	smaller_than_llmin(char *exit_code)
{
	int			ret;
	char		*n;
	char		*nn;
	const char	*min_ll = "-9223372036854775808";

	ret = LIE;
	if (exit_code[0] == '-')
	{
		n = trim_prefix(&exit_code[1], "0");
		nn = ft_calloc(ft_strlen(n) + 2, sizeof(char));
		ft_strlcat(nn, &exit_code[0], 2);
		ft_strlcat(nn, n, ft_strlen(n) + 2);
		if (ft_strlen(nn) > ft_strlen(min_ll) || ft_strcmp(min_ll, nn) < 0)
			ret = TRUTH;
		free(n);
		free(nn);
	}
	return (ret);
}

int	bigger_than_llmax(char *exit_code)
{
	int			ret;
	char		*n;
	char		*nn;
	const char	*max_ll = "+9223372036854775807";

	ret = LIE;
	if (exit_code[0] == '+')
	{
		n = trim_prefix(&exit_code[1], "0");
		nn = ft_calloc(ft_strlen(n) + 2, sizeof(char));
		ft_strlcat(nn, &exit_code[0], 2);
		ft_strlcat(nn, n, ft_strlen(n) + 2);
		if (ft_strlen(nn) > ft_strlen(max_ll) || ft_strcmp(max_ll, nn) < 0)
			ret = TRUTH;
		free(nn);
	}
	else
	{
		n = trim_prefix(exit_code, "0");
		if (ft_strlen(n) > ft_strlen(&max_ll[1])
			|| ft_strcmp(&max_ll[1], n) < 0)
			ret = TRUTH;
	}
	free(n);
	return (ret);
}

char	*trim_prefix(const char *s1, const char *set)
{
	size_t	size;
	char	*trimmed;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1)
		s1++;
	size = ft_strlen(s1);
	trimmed = ft_calloc(size + 1, sizeof(char));
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, s1, size + 1);
	return (trimmed);
}
