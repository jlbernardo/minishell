/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:35:43 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/14 22:19:20 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_ll(char *nbr);

void	ft_exit(t_token *tk, t_ast *ast, t_hash **ht, int last_exit)
{
	long int	exit_code;

	exit_code = last_exit;
	ft_putendl_fd(tk->literal, 1);
	if ((tk->next && !ft_isdigit(*tk->next->literal))
		|| (tk->next && check_ll(tk->next->literal)))
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(tk->next->literal, 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit_code = 2;
	}
	else if (tk->next && tk->next->next)
	{
		ft_putendl_fd("bash: exit: too many arguments", 2);
		return ;
	}
	else if (tk->next)
		exit_code = ft_atol(tk->next->literal);
	free_ht(ht);
	finisher(tk, ast);
	exit(exit_code);
}

int	check_ll(char *nbr)
{
	const char	*max_ll = "9223372036854775807";
	const char	*min_ll = "-9223372036854775808";

	if (nbr[0] == '-')
	{
		if (ft_strlen(nbr) > ft_strlen(min_ll)
			|| ft_strcmp(min_ll, nbr) < 0)
			return (TRUTH);
	}
	else
	{
		if (ft_strlen(nbr) > ft_strlen(max_ll)
			|| ft_strcmp(max_ll, nbr) < 0)
			return (TRUTH);
	}
	return (LIE);
}
