/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynini <ynini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 08:11:46 by ynini             #+#    #+#             */
/*   Updated: 2025/03/05 03:59:41 by ynini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	ft_print2(const char *str, va_list args, int *len, int *i)
{
	if (str[*i] == 's')
		ft_putstr(va_arg(args, char *), len);
	else if (str[*i] == 'c')
		ft_putchar(va_arg(args, int), len);
	else if (str[*i] == '%')
		ft_putchar('%', len);
	else if (str[*i] == 'u')
		ft_putnbr(va_arg(args, unsigned int), 10, "0123456789", len);
	else if (str[*i] == 'p')
		ft_putnbr(va_arg(args, unsigned long), 'p', \
		"0123456789abcdef", len);
}

static void	skip_bonus(const char *str, va_list args, int *len, int *i)
{
	short	value;
	char	dig[1];

	value = 'H';
	dig[0] = 'd';
	while (str[*i] == ' ' || str[*i] == '#' || str[*i] == '+')
	{
		if (str[*i] == ' ' && dig[0] != '+')
			dig[0] = ' ';
		else if (str[*i] == '+')
			dig[0] = '+';
		else if (str[*i] == '#')
			value = 'X';
		*i += 1;
	}
	if (str[*i] == 'd' || str[*i] == 'i')
		ft_putnbr(va_arg(args, int), 10, dig, len);
	else if (str[*i] == 'x')
		ft_putnbr(va_arg(args, unsigned int), value + 32, \
		"0123456789abcdef", len);
	else if (str[*i] == 'X')
		ft_putnbr(va_arg(args, unsigned int), value, \
		"0123456789ABCDEF", len);
}

static void	ft_print1(const char *str, va_list args, int *len, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '%')
		{
			*i += 1;
			skip_bonus(str, args, len, i);
			ft_print2(str, args, len, i);
			if (!ft_strchr("cspdiuxX%", str[*i]))
				ft_putchar(str[*i], len);
		}
		else
			ft_putchar(str[*i], len);
		if (!str[*i])
			break ;
		*i += 1;
	}
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	int			i;
	int			len;

	if (write(1, 0, 0) == -1)
		return (-1);
	len = 0;
	i = 0;
	va_start(args, str);
	ft_print1(str, args, &len, &i);
	va_end(args);
	return (len);
}
