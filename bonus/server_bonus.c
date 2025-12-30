/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagunduz <yagunduz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:30:00 by yagunduz          #+#    #+#             */
/*   Updated: 2025/12/30 19:05:21 by yagunduz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char	char_buffer = 0;
	static int				bits_received = 0;

	(void)context;
	if (sig == SIGUSR1)
		char_buffer = (char_buffer << 1) | 1;
	else
		char_buffer = (char_buffer << 1);
	bits_received++;
	if (bits_received == 8)
	{
		if (char_buffer == 0)
			write(1, "\n", 1);
		else
			write(1, &char_buffer, 1);
		char_buffer = 0;
		bits_received = 0;
	}
	if (info && info->si_pid != 0)
		kill(info->si_pid, SIGUSR1);
}

static void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		write(2, "Error: sigaction failed\n", 24);
		exit(1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(2, "Error: sigaction failed\n", 24);
		exit(1);
	}
}

int	main(void)
{
	write(1, "Server PID: ", 12);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	setup_signal_handlers();
	while (1)
		pause();
	return (0);
}
