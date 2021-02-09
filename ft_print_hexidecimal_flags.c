/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexidecimal_flags.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 14:27:44 by maadam            #+#    #+#             */
/*   Updated: 2020/07/27 14:27:44 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_print_hex_precision(int *num_len, int *len, t_flags *spec)
{
	int	i;

	i = 0;
	while (i++ < (spec->precision - *num_len))
		ft_putchar('0', len);
	(*num_len) += i - 1;
}

static void	ft_print_hex_width_part_three(int i, int *len,
										t_flags *spec)
{
	if (spec->nul == 0)
	{
		while (i++ < (spec->width - spec->size))
			ft_putchar(' ', len);
	}
	if (spec->nul == 1)
	{
		if (spec->pre_for_hex == 0 && spec->precision == 0 && spec->dot == 1)
		{
			i -= spec->specifier == 5 ? 1 : 0;
			while (i++ < (spec->width - spec->size))
				ft_putchar(' ', len);
			return ;
		}
		i -= spec->width == spec->precision ? 1 : 0;
		while (i++ < (spec->width - spec->size))
			ft_putchar('0', len);
	}
	if (((spec->specifier == 5 && spec->dot == 1 && spec->width <
		spec->precision && spec->width < spec->pre_for_hex) ||
		((spec->precision == 0 && spec->pre_for_hex == 0) && spec->dot == 1))
		&& spec->width > spec->size && spec->specifier == 5)
		ft_putchar(' ', len);
	else if (spec->flag_for_some && spec->minus == 1 && spec->width == 0)
		ft_putchar(' ', len);
}

static int	ft_print_hex_width_part_two(int i, int *len, int *num_len,
										t_flags *spec)
{
	int flag;

	flag = 1;
	if (spec->minus && spec->dot && spec->specifier != 5)
	{
		while (i++ < (spec->width - (*num_len)))
			ft_putchar('0', len);
		(*num_len)--;
		return (flag = 0);
	}
	else if (flag)
	{
		while (i++ < (spec->width - *num_len))
			ft_putchar(' ', len);
		return (flag);
	}
	return (0);
}

static void	ft_print_hex_width_part_one_else(int *len, t_flags *spec)
{
	int i;

	i = 0;
	if (spec->nul == 0 && spec->dot == 1)
	{
		if (spec->num_was_min == 1)
			i++;
		while (i++ < (spec->width - spec->precision))
			ft_putchar(' ', len);
	}
}

void		ft_print_hex_width_part_one(int *num_len, int *len, t_flags *spec)
{
	int i;
	int flag;

	i = 0;
	flag = 1;
	if (spec->specifier == 5 && spec->dot && spec->precision == 0 &&
		spec->width == 1 && spec->pre_was_min == 0)
	{
		ft_putchar(' ', len);
		return ;
	}
	if (spec->nul == 1 && spec->dot == 0)
	{
		while (i++ < (spec->width - *num_len))
			ft_putchar('0', len);
	}
	if (spec->flag_for_some && spec->specifier == 5)
	{
		flag = ft_print_hex_width_part_two(i, len, num_len, spec);
		spec->specifier++;
	}
	else if (flag)
		ft_print_hex_width_part_three(i, len, spec);
	else
		ft_print_hex_width_part_one_else(len, spec);
}
