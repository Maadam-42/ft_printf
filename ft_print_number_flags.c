/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number_flags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 13:19:24 by maadam            #+#    #+#             */
/*   Updated: 2020/07/24 13:19:24 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_num_precision(long long int *number, int num_len,
								int *len, t_flags *spec)
{
	int	i;

	i = 0;
	if (spec->precision != spec->width)
	{
		if (*number < 0)
		{
			*number *= -1;
			ft_putchar('-', len);
			i--;
		}
		while (i++ < (spec->precision - num_len))
			ft_putchar('0', len);
	}
	else
	{
		if (*number < 0)
		{
			ft_putchar('-', len);
			*number *= -1;
			i--;
		}
		while (i++ < (spec->precision - num_len))
			ft_putchar('0', len);
	}
}

void	ft_print_num_space_nul(long long int *number, int num_len, int *len,
								t_flags *spec)
{
	int i;

	i = 0;
	if (*number < 0 && ((spec->dot == 1 || spec->precision_star == 1) &&
		spec->pre_was_min != 0))
	{
		*number *= -1;
		ft_putchar('-', len);
		while (i++ < (spec->width - num_len))
			ft_putchar('0', len);
	}
	else
	{
		while (i++ < (spec->width - num_len))
			ft_putchar(' ', len);
	}
}

void	ft_print_num_space(int *len, t_flags *spec)
{
	int i;

	i = 0;
	while (i++ < spec->width)
		ft_putchar(' ', len);
}
