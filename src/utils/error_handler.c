/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:25:16 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/03/04 18:06:19 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	syntax_error(t_token *token, t_meta *meta)
{
	char	*err_tk;

	if (token)
		err_tk = token->literal;
	else
		err_tk = "newline";
	ft_putstr_fd("minishell: syntax error near unexpected token `", \
		STDERR_FILENO);
	ft_putstr_fd(err_tk, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	add_upd_hashtable("?", "2", meta->hash);
}

void	handle_null_pathname(t_cmd *cmd, t_meta *meta)
{
	if (cmd->word_list == NULL)
			return;
	ft_putstr_fd(cmd->word_list->word, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	add_upd_hashtable("?", "127", meta->hash);
}

void	path_error(t_meta *meta, char *path, char *msg, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	finisher(*meta, "ATHE", exit_code);
}

void	print_nsf_error_msg(char *filename)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
}

void	print_np_error_msg(char *filename)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putendl_fd(": Permission denied", STDERR_FILENO);
}
