/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:26:25 by msilva-p          #+#    #+#             */
/*   Updated: 2022/12/12 12:09:30 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	ft_exit(int ret, char *message)
{
	if (message)
		ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 1);
	exit(ret);
}

static void	print_signal(int signal, siginfo_t *info, void *ucontext)
{
	static int	shift_bits;
	static char	letter;

	(void)ucontext;
	if (signal == SIGUSR1)
		letter += (0b00000001 << shift_bits);
	if (shift_bits == 7)
	{
		if (letter)
			ft_putchar_fd(letter, 1);
		else
		{
			if (kill(info->si_pid, SIGUSR2))
				ft_exit(1, "Failed to send signal");
		}	
		letter = 0;
		shift_bits = 0;
	}
	else
		shift_bits++;
	if (kill(info->si_pid, SIGUSR1))
		ft_exit(1, "Failed to send signal");
}

int	main(void)
{
	struct sigaction	mt;

	ft_bzero(&mt, sizeof (struct sigaction));
	mt.sa_flags = SA_SIGINFO;
	mt.sa_sigaction = print_signal;
	if (sigaction(SIGUSR1, &mt, NULL))
		ft_exit(1, "Failed to configure signal function");
	if (sigaction(SIGUSR2, &mt, NULL))
		ft_exit(1, "Failed to configure signal function");
	ft_printf("PID: %d\n", (int)getpid());
	while (1)
		pause();
	return (0);
}
