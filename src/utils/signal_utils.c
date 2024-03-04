/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:50:55 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/03/04 14:30:48 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	basic_sigint(int signo)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_received_signal = signo;
}

void	eof_basic(t_meta *meta)
{
	int		exit_code;

	exit_code = last_exit(meta);
	ft_putendl_fd("exit", STDOUT_FILENO);
	finisher(*meta, "ATHE", exit_code);
}

void	heredoc_sigint(int signo)
{
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
	g_received_signal = signo;
}

int	signal_received(char *input, t_redir *r, int fd, t_meta *meta)
{
	if (g_received_signal == SIGINT)
	{
		close(fd);
		finisher(*meta, "ATHE", EXIT_FAILURE);
	}
	if (input == NULL)
	{
		close(fd);
		ft_putstr_fd("minishell: warning: here-document delimited by"
			" end-of-file (wanted `", STDERR_FILENO);
		ft_putstr_fd(r->filename, STDERR_FILENO);
		ft_putendl_fd("')", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
