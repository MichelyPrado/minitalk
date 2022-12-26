/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:26:12 by msilva-p          #+#    #+#             */
/*   Updated: 2022/12/12 14:34:30 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	g_stay;

static void	signal_receive(int signal)
{
	if (signal == SIGUSR1)
		g_stay = 0;
	else
		ft_printf("Message sent successfully!\n");
}

void	ft_exit(int ret, char *message)
{
	if (message)
		ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 1);
	exit(ret);
}

static void	tell_signal(int pid, char msg)
{
	int	count_bits;

	count_bits = 0;
	while (count_bits < 8)
	{
		if (g_stay == 0)
		{
			g_stay = 1;
			if ((msg >> count_bits) & 0b00000001)
			{
				if (kill(pid, SIGUSR1))
					ft_exit(1, "Failed to send signal");
			}
			else
			{
				if (kill(pid, SIGUSR2))
					ft_exit(1, "Failed to send signal");
			}
			count_bits++;
		}
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	mt;
	pid_t				pid;

	g_stay = 0;
	pid = ft_atoi(argv[1]);
	if (argc != 3)
		ft_exit(1, "Invalid number of arguments");
	if (pid <= 0)
		ft_exit(1, "Invalid PID");
	ft_bzero(&mt, sizeof (struct sigaction));
	mt.sa_handler = &signal_receive;
	sigaction(SIGUSR1, &mt, NULL);
	sigaction(SIGUSR2, &mt, NULL);
	while (*argv[2])
	{
		tell_signal(pid, *argv[2]);
		argv[2]++;
	}	
	tell_signal(pid, '\n');
	tell_signal(pid, '\0');
	usleep(100);
}
