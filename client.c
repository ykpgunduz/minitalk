/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagunduz <yagunduz@student.42istanbul.tr>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-12 13:07:07 by yagunduz          #+#    #+#             */
/*   Updated: 2025-11-12 13:07:07 by yagunduz         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	g_ack_flag = 0;

static void	handler_ack(int sig)
{
	(void)sig;
	g_ack_flag = 1;
}

static void	send_char_bits(pid_t target_pid, unsigned char ch)
{
	int	bit_index;

	bit_index = 7;
	while (bit_index >= 0)
	{
		g_ack_flag = 0;
		if ((ch >> bit_index) & 1)
			kill(target_pid, SIGUSR1);
		else
			kill(target_pid, SIGUSR2);
		while (!g_ack_flag)
			pause();
		bit_index--;
	}
}

int	main(int argc, char **argv)
{
	pid_t				target_pid;
	int					i;
	int					len;
	struct sigaction	sa;

	if (argc != 3)
		return (write(2, "Usage: ./client <pid> <message>\n", 33), 1);
	len = 0;
	while (argv[1][len])
		len++;
	if (len > 7)
		return (write(2, "Error: PID too long\n", 20), 1);
	target_pid = ft_atoi(argv[1]);
	if (target_pid <= 0 || target_pid >= 4194304)
		return (write(2, "Error: Invalid PID\n", 19), 1);
	if (kill(target_pid, 0) == -1)
		return (write(2, "Error: Invalid PID\n", 19), 1);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler_ack;
	sigaction(SIGUSR1, &sa, NULL);
	i = 0;
	while (argv[2][i])
		send_char_bits(target_pid, (unsigned char)argv[2][i++]);
	send_char_bits(target_pid, '\0');
}
