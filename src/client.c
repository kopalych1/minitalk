/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:26:27 by akostian          #+#    #+#             */
/*   Updated: 2024/08/19 18:14:51 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	send_char(pid_t pid, char chr)
{
	char			buffer[9];
	int				i;

	i = 0;
	while (chr)
	{
		buffer[i++] = "01"[chr % 2];
		chr /= 2;
	}
	while (i < 8)
		buffer[i++] = '0';
	while (i--)
	{
		if (buffer[i] - '0')
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(1000 * 0.2);
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
	ft_printf("Sent: \"%s\"", text);
	while (*text)
	{
		send_char(pid, *text);
		text++;
	}
	ft_printf("\n");
	return (0);
}
