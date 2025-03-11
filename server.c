/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynini <ynini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:18:53 by ynini             #+#    #+#             */
/*   Updated: 2025/03/07 15:59:40 by ynini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int signum, siginfo_t *info, void *context)
{
	static char		character;
	static int		count_bit;
	static pid_t	last_pid;

	(void)context;
	if (last_pid != info->si_pid)
	{
		character = 0;
		count_bit = 0;
		last_pid = info->si_pid;
	}
	character = (character << 1) | (signum == SIGUSR2);
	count_bit++;
	if (count_bit == 8)
	{
		write(1, &character, 1);
		character = 0;
		count_bit = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	pid = getpid();
	ft_printf("%d\n", pid);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	while (1)
		pause();
}
