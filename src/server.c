/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:25:31 by akostian          #+#    #+#             */
/*   Updated: 2024/08/19 18:15:43 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static char		chr = 0;
	static int		i = 0;

	(void)context;
	(void)info;
	i++;
	chr = (chr << 1) + (signum == 10);
	if (i == 8)
	{
		ft_printf("%c", chr);
		i = 0;
		chr = 0;
	}
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
		;
	return (0);
}
