/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynini <ynini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 06:42:21 by ynini             #+#    #+#             */
/*   Updated: 2025/03/08 03:12:20 by ynini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	send_null_terminator(pid_t pid)
{
	int	num_bits;

	num_bits = 7;
	while (num_bits >= 0)
	{
		kill(pid, SIGUSR1);
		usleep(200);
		usleep(200);
		num_bits--;
	}
}

int	send_text(char **av)
{
	pid_t	pid;
	int		i;
	int		num_bits;

	i = 0;
	pid = ft_atoi(av[1]);
	if (pid <= 0)
		exit(1);
	while (av[2][i])
	{
		num_bits = 7;
		while (num_bits >= 0)
		{
			if ((av[2][i] >> num_bits) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(200);
			usleep(200);
			num_bits--;
		}
		i++;
	}
	send_null_terminator(pid);
	return (0);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	msg_recieved(int signum)
{
	(void)signum;
	ft_printf("Message has recieved.\n");
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sa.sa_handler = msg_recieved;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (ac != 3)
		return (1);
	if (is_numeric(av[1]))
		return (1);
	send_text(av);
	exit(0);
	pause();
}
