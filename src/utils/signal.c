/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:16:50 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/03/05 17:17:59 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	basic_signal(t_meta *meta)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_handler = basic_sigint;
	sig_int.sa_flags = 0;
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_handler = SIG_IGN;
	sig_quit.sa_flags = 0;
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
	tcsetattr(STDIN_FILENO, TCSANOW, meta->term);
	meta->cmd_nbr = 0;
	g_received_signal = 0;
}

void	execution_signal(int child_pid)
{
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	if (child_pid == 0)
		sig.sa_handler = SIG_DFL;
	else
		sig.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig, NULL);
	sigaction(SIGINT, &sig, NULL);
}

void	heredoc_signal(int child_pid)
{
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	if (child_pid == 0)
		sig.sa_handler = heredoc_sigint;
	else
		sig.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sig, NULL);
}
