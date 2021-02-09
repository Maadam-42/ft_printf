/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_part_two.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 21:14:32 by maadam            #+#    #+#             */
/*   Updated: 2020/07/29 21:14:32 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_check_flag(const char *f_ptr, int *i)
{
	int flag;

	flag = 0;
	if (f_ptr[--(*i)] == '%')
	{
		flag++;
		(*i)++;
	}
	if (f_ptr[*i] == 'c' || f_ptr[*i] == 's' || f_ptr[*i] == 'd' ||
		f_ptr[*i] == 'i' || f_ptr[*i] == 'u' || f_ptr[*i] == 'x' ||
		f_ptr[*i] == 'X' || f_ptr[*i] == 'p')
		return (flag += 1);
	return (flag);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	if (!(s) || !(n))
		return ;
	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

void	ft_check_struct(t_flags *spec)
{
	spec->flag_for_some = (spec->precision < 0) ? 1 : 0;
	spec->pre_was_min = (spec->precision < 0) ? 1 : 0;
	if (spec->precision < 0)
		spec->pre_for_hex = spec->precision * -1;
	spec->precision = (spec->precision < 0) ? 0 : spec->precision;
	spec->hex_nul = spec->nul;
	spec->nul = spec->precision ? 0 : spec->nul;
	spec->specifier = 2;
}
