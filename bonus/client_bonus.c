/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagunduz <yagunduz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:30:00 by yagunduz          #+#    #+#             */
/*   Updated: 2025/12/30 19:49:10 by yagunduz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static volatile sig_atomic_t	g_response_flag = 0;

static void	receive_acknowledgement(int sig)
{
	(void)sig;
	g_response_flag = 1;
}

static void	transmit_byte(pid_t pid, unsigned char byte)
{
	int			bit;
	sigset_t	mask;
	sigset_t	orig_mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigprocmask(SIG_BLOCK, &mask, &orig_mask);
	bit = 7;
	while (bit >= 0)
	{
		g_response_flag = 0;
		if ((byte >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_response_flag)
			sigsuspend(&orig_mask);
		bit--;
	}
	sigprocmask(SIG_SETMASK, &orig_mask, NULL);
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	int					i;
	struct sigaction	sa;

	if (argc != 3)
		return (write(2, "Usage: ./client <pid> <msg>\n", 29), 1);
	pid = ft_atoi(argv[1]);
	if (pid <= 0 || kill(pid, 0) == -1)
		return (write(2, "Error: Invalid PID\n", 19), 1);
	sa.sa_handler = receive_acknowledgement;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	i = 0;
	while (argv[2][i])
		transmit_byte(pid, (unsigned char)argv[2][i++]);
	transmit_byte(pid, '\0');
	write(1, "Message sent!\n", 14);
	return (0);
}
