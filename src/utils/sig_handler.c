/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:16:50 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/02/25 23:13:22 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_handler = sig_deal;
	sig_int.sa_flags = 0;
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_handler = SIG_IGN;
	sig_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sig_quit, NULL);
	sigaction(SIGINT, &sig_int, NULL);
}

void	sig_deal(int signo)
{
	(void)signo;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
