/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexidecimal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 13:14:25 by maadam            #+#    #+#             */
/*   Updated: 2020/07/27 13:14:25 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_x_p_part_two(unsigned long int number,
									int *len, t_flags *spec)
{
	if (spec->p_char == 'p')
		ft_putstr("0x", 2, len, spec);
	ft_print_hexidecimal(number, len, spec);
}

static void	ft_print_hex_width_part_one_if(unsigned long int number,
											int *len, t_flags *spec)
{
	if (((number == 0 && ((spec->minus == 1 && spec->width == 0)) &&
		spec->pre_for_hex == 0 && spec->precision == 0)) ||
		(number == 0 && spec->pre_was_min == 1 && spec->specifier == 5))
		ft_putchar('0', len);
	else if (number == 0 && spec->minus && spec->dot && spec->precision == 0 &&
			spec->width == 1)
		ft_putchar(' ', len);
}

static void	ft_print_x_p_part_one(unsigned long int number, int *num_len,
									int *len, t_flags *spec)
{
	int flag;
	int dot;

	flag = 1;
	dot = spec->dot ? 1 : 0;
	if ((spec->dot == 1 && spec->width == 0) && dot--)
		ft_print_hex_precision(num_len, len, spec);
	if (((spec->minus && spec->width != 0 && spec->dot == 0)
		|| (spec->flag_for_some && spec->specifier != 5)
		|| (number == 0 && spec->flag_for_some && spec->width > 1)) && flag--)
		ft_print_x_p_part_two(number, len, spec);
	if ((spec->width != 0 && spec->width > *num_len && spec->dot == 0) ||
		(spec->minus == 0 && spec->width != 0))
		ft_print_hex_width_part_one(num_len, len, spec);
	if ((spec->precision > 0 && spec->precision >= *num_len && dot == 1) ||
		spec->hex_nul)
		ft_print_hex_precision(num_len, len, spec);
	if ((flag && number != 0) || (number == 0 && spec->dot == 0 &&
		spec->minus == 0) || (spec->precision))
		ft_print_x_p_part_two(number, len, spec);
	if (spec->width != 0 && spec->width > *num_len && spec->dot == 1 &&
		spec->minus == 1)
		ft_print_hex_width_part_one(num_len, len, spec);
	ft_print_hex_width_part_one_if(number, len, spec);
}

static void	ft_print_x_p_short_part(unsigned long int number,
									int *len, t_flags *spec)
{
	int num_len;

	num_len = ft_hex_point_len(number);
	num_len += (spec->p_char == 'p') ? 2 : 0;
	spec->size = (num_len > spec->precision) ? num_len : spec->precision;
	ft_print_x_p_part_one(number, &num_len, len, spec);
}

void		ft_hexidecimal_pointer(const char ch, int *len,
									t_flags *spec, va_list ap)
{
	unsigned long int	number;

	number = 0;
	if (ch == 'x' || ch == 'X')
		number = va_arg(ap, unsigned int);
	if (ch == 'p')
		number = va_arg(ap, unsigned long int);
	if (ch == 'p' && number == 0)
	{
		ft_print_null_pointer(len, spec);
		if (number == 0 && spec->pre_was_min == 1)
			ft_putchar('0', len);
		return ;
	}
	if (ch != 'p' && number == 0 && spec->dot == 1 && spec->precision == 0 &&
		spec->width == 0 && spec->pre_was_min == 0)
		return ;
	spec->p_char = ch;
	spec->nul = spec->minus ? 0 : spec->nul;
	spec->specifier = (number == 0) ? 5 : spec->specifier;
	spec->flag_for_some = (spec->minus && spec->width > 1 && spec->dot == 1 &&
							spec->pre_was_min) ? 1 : 0;
	if (ch == 'x' || ch == 'X' || ch == 'p')
		ft_print_x_p_short_part(number, len, spec);
}
