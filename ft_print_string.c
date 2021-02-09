/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:37:06 by maadam            #+#    #+#             */
/*   Updated: 2020/07/23 11:37:06 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_putstr(const char *str, int str_len, int *len, t_flags *spec)
{
	int i;

	i = 0;
	while (str[i] != '\0' && str_len > 0)
	{
		ft_putchar(str[i], len);
		i++;
		str_len--;
	}
	spec->specifier = 5;
}

static	void	ft_print_str_width(int str_len, int *len, t_flags *spec)
{
	int i;

	i = 0;
	if (spec->nul == 0 || spec->specifier == 5)
	{
		while (i++ < (spec->width - str_len))
			ft_putchar(' ', len);
	}
	if (spec->nul == 1 && spec->specifier != 5)
	{
		while (i++ < (spec->width - str_len))
			ft_putchar('0', len);
	}
	else
	{
		while (i++ < (spec->width - str_len))
			ft_putchar('0', len);
	}
}

static void		ft_string_part(const char *str, int str_len,
								int *len, t_flags *spec)
{
	if (spec->width > str_len && spec->minus == 0)
	{
		ft_print_str_width(str_len, len, spec);
		ft_putstr(str, str_len, len, spec);
	}
	else if (spec->width > str_len && spec->minus == 1)
	{
		ft_putstr(str, str_len, len, spec);
		ft_print_str_width(str_len, len, spec);
	}
	else
		ft_putstr(str, str_len, len, spec);
}

void			ft_string(const char ch, int *len,
							t_flags *spec, va_list ap)
{
	char	*str;
	int		str_len;

	str_len = 0;
	if (ch == 's')
		str = va_arg(ap, char *);
	if (ch == 's' && str == NULL)
		str = "(null)";
	if (ch == 's')
	{
		str_len = ft_strlen(str);
		if (spec->flag_for_some == 0)
			str_len = (spec->dot > 0 && spec->precision < ft_strlen(str)) ?
				spec->precision : ft_strlen(str);
		if (spec->flag_for_some == 1)
		{
			spec->precision = -1;
			spec->flag_for_some = 0;
		}
		if (spec->dot == 1 && spec->precision == 0 && spec->width == 0 &&
			spec->flag_for_some == 1)
			return ;
		ft_string_part(str, str_len, len, spec);
	}
}
