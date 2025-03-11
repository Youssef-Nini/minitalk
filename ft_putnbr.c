/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynini <ynini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:59:17 by ynini             #+#    #+#             */
/*   Updated: 2024/11/23 21:42:15 by ynini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putaddress(unsigned long n, char *digits, int *len)
{
	if (n >= 16)
		ft_putaddress(n / 16, digits, len);
	ft_putchar(digits[n % 16], len);
}

static void	check_bonus(long long n, int base, char *digits, int *len)
{
	if (base == 'x' || base == 'X' || base == 'h' || base == 'H' )
	{
		if (base == 'x' && n != 0)
			ft_putstr("0x", len);
		else if (base == 'X' && n != 0)
			ft_putstr("0X", len);
		ft_putnbr(n, 16, digits, len);
	}
	if (digits[0] == ' ' || digits[0] == '+' || digits[0] == 'd')
	{
		if (digits[0] == ' ' && n >= 0)
			ft_putchar(' ', len);
		else if (digits[0] == '+' && n >= 0)
			ft_putchar('+', len);
		ft_putnbr(n, 10, "0123456789", len);
	}
}

void	ft_putnbr(long long n, int base, char *digits, int *len)
{
	if (base == 'p')
	{
		ft_putstr("0x", len);
		ft_putaddress(n, digits, len);
		return ;
	}
	else if ((base != 16 && base != 10) || digits[0] != '0')
	{
		check_bonus(n, base, digits, len);
		return ;
	}
	if (n < 0 && base != 16)
	{
		ft_putchar('-', len);
		n *= -1;
	}
	if (n >= base)
		ft_putnbr(n / base, base, digits, len);
	ft_putchar(digits[n % base], len);
}
