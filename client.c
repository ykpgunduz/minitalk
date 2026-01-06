/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagunduz <yagunduz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:07:07 by yagunduz          #+#    #+#             */
/*   Updated: 2026/01/06 13:56:19 by yagunduz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	g_confirmation = 0;

static void	signal_confirmation(int sig)
{
	(void)sig;
	g_confirmation = 1;
}

static void	send_char_bits(pid_t target_pid, unsigned char chr)
{
	int			bit_index;
	sigset_t	mask;
	sigset_t	orig_mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigprocmask(SIG_BLOCK, &mask, &orig_mask);
	bit_index = 7;
	while (bit_index >= 0)
	{
		g_confirmation = 0;
		if ((chr >> bit_index) & 1)
			kill(target_pid, SIGUSR1);
		else
			kill(target_pid, SIGUSR2);
		while (!g_confirmation)
			sigsuspend(&orig_mask);
		bit_index--;
	}
	sigprocmask(SIG_SETMASK, &orig_mask, NULL);
}

int	main(int argc, char **argv)
{
	pid_t				target_pid;
	int					i;
	struct sigaction	sa;

	if (argc != 3)
	{
		return (write(2, "Usage: ./client <pid> <message>\n", 33), 1);
	}
	target_pid = ft_atoi(argv[1]);
	if (target_pid <= 0 || kill(target_pid, 0) == -1)
	{
		return (write(2, "Error: Invalid PID\n", 19), 1);
	}
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = signal_confirmation;
	sigaction(SIGUSR1, &sa, NULL);
	i = 0;
	while (argv[2][i])
	{
		send_char_bits(target_pid, (unsigned char)argv[2][i]);
		i++;
	}
	send_char_bits(target_pid, '\0');
	return (0);
}
