/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:26:27 by akostian          #+#    #+#             */
/*   Updated: 2024/10/02 10:09:49 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

unsigned char	get_nth_bit(int c, unsigned char bit_n)
{
	return (c >> bit_n & 1);
}

void	send_byte(pid_t pid, char chr)
{
	unsigned char	i;

	i = 8;
	while (i--)
	{
		if (get_nth_bit(chr, i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(BIT_WAIT_TIME_USECONDS);
	}
}

void	signal_handler(int sig)
{
	static int	recived = 0;

	if (sig == SIGUSR1)
		recived++;
	else
	{
		ft_printf("Recived: %d\n", recived);
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*text;

	if (argc != 3)
		return (ft_printf("ARGUMENTS INCORRECT\n"), 1);
	text = argv[2];
	if (!ft_strlen(text))
		return (ft_printf("STRING IS EMPTY\n"), 1);
	pid = ft_atoi(argv[1]);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	ft_printf("Sent: \"%s\", %d\n", argv[2], ft_strlen(argv[2]));
	while (*text)
		send_byte(pid, *text++);
	send_byte(pid, 0);
	while (1)
		pause();
	return (0);
}
