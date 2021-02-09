/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexidecimal_part_two.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 23:09:30 by maadam            #+#    #+#             */
/*   Updated: 2020/08/01 23:09:30 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_null_pointer(int *len, t_flags *spec)
{
	char	*str;
	int		str_len;
	int		i;

	i = 0;
	str = (spec->dot == 1 && spec->precision == 0) ? "0x" : "0x0";
	str_len = ft_strlen(str);
	if (spec->width != 0)
	{
		if (spec->minus)
			ft_putstr(str, str_len, len, spec);
		while (i++ < (spec->width - str_len))
			ft_putchar(' ', len);
	}
	if (spec->minus == 0)
		ft_putstr(str, str_len, len, spec);
}

void	ft_print_hexidecimal(unsigned long int number,
							int *len, t_flags *spec)
{
	int			mirror_hex[30];
	const char	*digits;
	int			i;

	digits = "0123456789abcdef";
	i = 0;
	while (number >= 16)
	{
		mirror_hex[i] = number % 16;
		i++;
		number /= 16;
	}
	if (spec->p_char == 'X')
	{
		ft_putchar(ft_toupper(digits[number]), len);
		while (i-- > 0)
			ft_putchar(ft_toupper(digits[mirror_hex[i]]), len);
	}
	else
	{
		ft_putchar(digits[number], len);
		while (i-- > 0)
			ft_putchar(digits[mirror_hex[i]], len);
	}
}
