/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number_flags_if.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 21:39:22 by maadam            #+#    #+#             */
/*   Updated: 2020/08/01 21:39:22 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_else_if_nul(long long int *number, int num_len,
						int *len, t_flags *spec)
{
	int i;

	i = 0;
	if (spec->num_was_min == 1)
		i++;
	if (*number != 0)
	{
		while (i++ < (spec->width - spec->precision))
			ft_putchar(' ', len);
	}
	else if (*number == 0)
	{
		if (spec->flag_for_some == 1)
		{
			while (i++ < (spec->width - num_len))
				ft_putchar(' ', len);
		}
		else
		{
			while (i++ < (spec->width - spec->precision))
				ft_putchar(' ', len);
		}
	}
}

static void	ft_if_nul_short_part(int num_len, int *len, t_flags *spec)
{
	int i;

	i = 0;
	if (((spec->precision_star == 1 && spec->precision == 0) ||
		(spec->dot_was && spec->dot == 0)) && spec->pre_was_min == 0)
	{
		while (i++ < (spec->width - num_len))
			ft_putchar(' ', len);
	}
	else
	{
		while (i++ < (spec->width - num_len))
			ft_putchar('0', len);
	}
}

static void	ft_if_nul(long long int *number, int num_len,
						int *len, t_flags *spec)
{
	int i;

	i = 0;
	if (*number < 0)
	{
		if ((spec->dot == 1 || spec->precision_star == 1) &&
			spec->precision == 0)
		{
			ft_print_num_space_nul(number, num_len, len, spec);
			return ;
		}
		*number *= -1;
		ft_putchar('-', len);
	}
	if ((spec->dot == 0 && spec->precision >= 0 && *number != 0 &&
		spec->num_was_min == 0) || spec->num_was_min == 1 || (spec->width &&
		spec->dot == 0) || (*number == 0 && spec->pre_was_min == 1))
		ft_if_nul_short_part(num_len, len, spec);
}

void		ft_print_num_width(long long int *number, int num_len, int *len,
							t_flags *spec)
{
	int i;

	i = 0;
	if (spec->nul == 1)
		ft_if_nul(number, num_len, len, spec);
	else if (spec->nul == 1 && spec->precision == 0 && spec->width > 0 &&
			spec->num_was_min == 0)
	{
		i = 0;
		while (i++ < spec->width - num_len)
			ft_putchar(' ', len);
	}
	if (spec->nul == 0 && spec->dot == 0)
	{
		while (i++ < (spec->width - num_len))
			ft_putchar(' ', len);
	}
	else if (spec->nul == 0 && spec->dot == 1)
		ft_else_if_nul(number, num_len, len, spec);
	else if (*number == 0 && spec->width > 0 && spec->precision == 0 &&
			spec->dot == 1 && spec->flag_for_some && spec->pre_was_min == 0)
		ft_print_num_space(len, spec);
}
