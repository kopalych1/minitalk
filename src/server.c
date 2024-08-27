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

#define BUFFER_SIZE 16

int	append_str(char **str1, char *str2)
{
	char	*old_str1;

	old_str1 = *str1;
	*str1 = ft_strjoin(*str1, str2);
	if (!*str1)
		return (-1);
	free(old_str1);
	return (0);
}

int	if_is_last(
		char chr,
		char **result,
		char buffer[BUFFER_SIZE + 1],
		int *buffer_index
)
{
	if (!chr)
	{
		if (append_str(result, buffer) == -1)
			return (ft_printf("MALLOC ERROR\n"), free(*result), -1);
		ft_printf("%s\n", *result);
		free(*result);
		*result = NULL;
		*buffer_index = 0;
	}
	return (0);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static char		chr = 0;
	static int		chr_iterator = 0;
	static char		*result;
	static char		buffer[BUFFER_SIZE + 1];
	static int		buffer_index = 0;

	(void)context;
	(void)info;
	chr_iterator++;
	chr = (chr << 1) + (signum == 10);
	if (chr_iterator != 8)
		return ;
	chr_iterator = 0;
	buffer[buffer_index++] = chr;
	if (buffer_index == BUFFER_SIZE)
	{
		buffer[buffer_index] = '\0';
		if (append_str(&result, buffer) == -1)
			return (ft_printf("MALLOC ERROR\n"), free(result));
		buffer_index = 0;
	}
	if (if_is_last(chr, &result, buffer, &buffer_index) == -1)
		return ;
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
		;
	return (0);
}
