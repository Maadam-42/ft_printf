/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:36:35 by maadam            #+#    #+#             */
/*   Updated: 2020/07/23 11:36:35 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				ft_print_number(long long int number,
										int *len, t_flags *spec)
{
	if (number == 0 && spec->dot != 0 && spec->precision == 0 &&
		spec->pre_was_min == 0)
		return ;
	if (number < 0)
	{
		ft_putchar('-', len);
		number *= -1;
		ft_print_number(number, len, spec);
	}
	else if (number >= 10)
	{
		ft_print_number(number / 10, len, spec);
		ft_putchar(number % 10 + '0', len);
	}
	else
		ft_putchar(number % 10 + '0', len);
	spec->specifier = 3;
}

static long long int	ft_num_len(long long int number)
{
	int	num_len;

	num_len = 0;
	if (number == 0)
		return (num_len = 1);
	if (number < 0)
		num_len = 1;
	while (number)
	{
		number /= 10;
		num_len++;
	}
	return (num_len);
}

static void				ft_numbers_part_two_if(long long int *number,
										int num_len, int *len, t_flags *spec)
{
	spec->flag_for_some = spec->flag_for_some > 0 ? 1 : 5;
	ft_print_num_width(number, num_len, len, spec);
	spec->flag_for_some = 5;
}

static void				ft_numbers_part_two(long long int *number, int num_len,
											int *len, t_flags *spec)
{
	int flag;

	flag = 1;
	if (spec->minus == 1 && spec->width != 0 && spec->precision == 0 &&
		(flag--))
		ft_print_number(*number, len, spec);
	flag = spec->minus ? 0 : 1;
	if ((spec->width > 0 && spec->width > num_len && spec->precision == 0) ||
		flag)
		ft_numbers_part_two_if(number, num_len, len, spec);
	if (spec->precision > 0 && spec->precision >= num_len)
		ft_print_num_precision(number, num_len, len, spec);
	flag++;
	if ((flag || *number != 0) && spec->specifier != 3)
		ft_print_number(*number, len, spec);
	if (spec->width > 0 && (spec->width > num_len) && spec->precision != 0 &&
		flag == 1)
	{
		ft_print_num_width(number, num_len, len, spec);
		spec->flag_for_some = 5;
	}
	if (*number == 0 && spec->width > 0 && spec->precision == 0 &&
		spec->minus == 1 && spec->flag_for_some != 5)
		ft_print_num_width(number, num_len, len, spec);
}

void					ft_numbers(const char ch, int *len,
								t_flags *spec, va_list ap)
{
	long long int	number;
	int				num_len;

	number = 0;
	if (ch == 'd' || ch == 'i')
		number = va_arg(ap, int);
	else if (ch == 'u')
		number = va_arg(ap, unsigned int);
	spec->num_was_min = (number < 0) ? 1 : 0;
	num_len = ft_num_len(number);
	spec->dot_was = spec->dot;
	spec->dot = (spec->precision < num_len && number != 0) ? 0 : spec->dot;
	spec->nul = spec->minus > 0 ? 0 : spec->nul;
	if (ch == 'd' || ch == 'i' || ch == 'u')
		ft_numbers_part_two(&number, num_len, len, spec);
}
