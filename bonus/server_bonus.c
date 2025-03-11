/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynini <ynini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:18:53 by ynini             #+#    #+#             */
/*   Updated: 2025/03/08 03:11:12 by ynini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	g_count_bit = 0;

void	handl_unicode(int *bytes_remaining, unsigned char *character)
{
	if (*bytes_remaining == 0)
	{
		if ((*character & 0x80) == 0)
			*bytes_remaining = 1;
		else if ((*character & 0xE0) == 0xC0)
			*bytes_remaining = 2;
		else if ((*character & 0xF0) == 0xE0)
			*bytes_remaining = 3;
		else if ((*character & 0xF8) == 0xF0)
			*bytes_remaining = 4;
	}
}

void	handl(unsigned char *character, int *buffer_index, \
int *bytes_remaining, unsigned char *buffer)
{
	handl_unicode(bytes_remaining, character);
	buffer[(*buffer_index)++] = *character;
	if (*character != '\0' && *buffer_index == *bytes_remaining)
	{
		write(1, buffer, *buffer_index);
		*bytes_remaining = 0;
		*buffer_index = 0;
	}
}

void	handler(int signum, siginfo_t *info, void *context)
{
	static unsigned char	character;
	static pid_t			last_pid;
	static unsigned char	buffer[4];
	static int				bytes_remaining;
	static int				buffer_index;

	(void)context;
	if (last_pid != info->si_pid)
	{
		character = 0;
		g_count_bit = 0;
		bytes_remaining = 0;
		buffer_index = 0;
		last_pid = info->si_pid;
	}
	character = (character << 1) | (signum == SIGUSR2);
	g_count_bit++;
	if (g_count_bit == 8)
	{
		handl(&character, &buffer_index, &bytes_remaining, buffer);
		if (character == '\0')
			kill(info->si_pid, SIGUSR1);
		character = 0;
		g_count_bit = 0;
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
