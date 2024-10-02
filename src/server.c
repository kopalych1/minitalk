/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:25:31 by akostian          #+#    #+#             */
/*   Updated: 2024/08/27 21:28:51 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static char				chr = 0;
	static unsigned char	chr_iterator = 0;

	(void)context;
	chr = (chr << 1) + (signum == SIGUSR1);
	if (++chr_iterator != 8)
		return ;
	chr_iterator = 0;
	if (!chr)
		kill(info->si_pid, SIGUSR2);
	else
		kill(info->si_pid, SIGUSR1);
	ft_putchar(chr);
	chr = 0;
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server started with PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
