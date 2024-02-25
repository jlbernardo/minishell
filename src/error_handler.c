/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:25:16 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/24 17:29:58 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", \
		STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

void	handle_null_pathname(char *cmd, t_meta *meta)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	add_or_upd_ht_entry("?", "127", meta->hash);
}

void	handle_forked_null_pathname(t_cmd *data, t_meta *meta)
{
	ft_putstr_fd(data->word_list->word, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	finisher(*meta);
	free_ht(meta->hash);
	close_all_fds();
	exit(127);
}
