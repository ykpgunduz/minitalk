/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagunduz <yagunduz@student.42istanbul.tr>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-12 13:07:07 by yagunduz          #+#    #+#             */
/*   Updated: 2025-11-12 13:07:07 by yagunduz         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static unsigned char	current_char = 0;
	static int				bit_count = 0;

	(void)context;
	if (sig == SIGUSR1)
		current_char = (current_char << 1) | 1;
	else
		current_char = (current_char << 1);
	bit_count++;
	if (bit_count == 8)
	{
		if (current_char == 0)
			write(1, "\n", 1);
		else
			write(1, &current_char, 1);
		current_char = 0;
		bit_count = 0;
	}
	if (info->si_pid != 0)
		kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	write(1, "Server PID: ", 12);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
