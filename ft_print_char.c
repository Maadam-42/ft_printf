/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 17:04:39 by maadam            #+#    #+#             */
/*   Updated: 2020/07/24 17:04:39 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_char_flags(char c, int *len, t_flags *spec)
{
	int i;

	i = 1;
	if (spec->minus == 1)
	{
		ft_putchar(c, len);
		while (i++ < spec->width)
			ft_putchar(' ', len);
		return (1);
	}
	else if (spec->minus == 0)
	{
		while (i++ < spec->width)
		{
			if (spec->nul == 1 || spec->hex_nul == 1)
				ft_putchar('0', len);
			else
				ft_putchar(' ', len);
		}
	}
	return (0);
}

void		ft_char(const char ch, int *len,
					t_flags *spec, va_list ap)
{
	char	c;
	int		print_flag;

	print_flag = 0;
	if (ch == 'c')
	{
		c = (char)va_arg(ap, int);
		if (spec->width > 0)
			print_flag = ft_print_char_flags(c, len, spec);
		if (print_flag == 0)
			ft_putchar(c, len);
	}
	else if (ch == '%')
	{
		if (spec->width > 0)
			print_flag = ft_print_char_flags('%', len, spec);
		if (print_flag == 0)
			ft_putchar('%', len);
	}
}
