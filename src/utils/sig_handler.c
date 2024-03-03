/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:16:50 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/03/03 12:47:45 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(t_meta *meta)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_handler = sig_deal;
	sig_int.sa_flags = 0;
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_handler = SIG_IGN;
	sig_quit.sa_flags = 0;
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
	g_received_signal = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, meta->term);
	meta->cmd_nbr = 0;
}

void	sig_deal(int signo)
{
	(void)signo;
	g_received_signal = SIGINT;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	mid_exec_signal(int child_pid)
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

void	eof_signal(t_meta *meta)
{
	int		exit_code;

	exit_code = last_exit(meta);
	ft_putendl_fd("exit", STDOUT_FILENO);
	finisher(*meta, "ATHE", exit_code);
}

void	heredoc_sigint_handler(int signum)
{
	write(1, "\n", 1);
	close(STDIN_FILENO);
	if (signum == SIGINT)
		g_received_signal = SIGINT;
}
