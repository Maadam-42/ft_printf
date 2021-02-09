/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 13:26:38 by maadam            #+#    #+#             */
/*   Updated: 2020/07/16 13:26:38 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_check_stars(const char *f_ptr, int *i, t_flags *spec, va_list ap)
{
	if (f_ptr[*i] == '*')
	{
		if (spec->dot == 0 && (spec->width_star = 1))
		{
			spec->width = va_arg(ap, int);
			if (spec->width < 0)
			{
				spec->width *= -1;
				spec->minus = 1;
			}
		}
		if (spec->dot == 1 && (spec->precision_star = 1))
		{
			spec->precision = va_arg(ap, int);
		}
		(*i)++;
		if (f_ptr[*i] == '.')
		{
			spec->dot = 1;
			if (f_ptr[++(*i)] == '*')
				ft_check_stars(f_ptr, i, spec, ap);
		}
	}
}

static void	ft_check_flags(const char *f_ptr, int *i, t_flags *spec, va_list ap)
{
	while (f_ptr[*i] != '\0' && (f_ptr[*i] == '-' || f_ptr[*i] == '+' ||
			f_ptr[*i] == ' ' || f_ptr[*i] == '.' || f_ptr[*i] == '0'))
	{
		if (f_ptr[*i] == '+')
			spec->plus = 1;
		else if (f_ptr[*i] == '-')
			spec->minus = 1;
		else if (f_ptr[*i] == '0')
			spec->nul = 1;
		else if (f_ptr[*i] == ' ')
			spec->space = 1;
		else if (f_ptr[*i] == '.')
			spec->dot = 1;
		else if (f_ptr[*i] == '#')
			spec->octotorp = 1;
		(*i)++;
	}
	ft_check_stars(f_ptr, i, spec, ap);
	spec->width = (spec->width_star == 0 && spec->dot == 0) ?
					ft_atoi(f_ptr, i, spec) : spec->width;
	ft_check_stars(f_ptr, i, spec, ap);
	spec->precision = (spec->precision_star == 1 && spec->dot == 1) ?
						spec->precision : ft_atoi(f_ptr, i, spec);
	ft_check_struct(spec);
}

static int	ft_check_percent(const char *f_ptr, int *i, int *len, t_flags *spec)
{
	int k;
	int per_count;
	int specifier;

	k = 0;
	per_count = 0;
	specifier = 0;
	(*i)--;
	while (f_ptr[k] == '%')
	{
		per_count++;
		k++;
		(*i)++;
	}
	specifier = per_count % 2;
	spec->percent = (specifier == 0) ? 0 : 1;
	per_count /= 2;
	while (per_count--)
		ft_putchar('%', len);
	return (specifier);
}

static void	ft_parsing(const char *f_ptr, int *i, int *len, va_list ap)
{
	t_flags		spec;
	int			flag;

	ft_bzero(&spec, sizeof(spec));
	spec.specifier = 1;
	if (f_ptr[++(*i)] == '%')
		spec.specifier = ft_check_percent(&f_ptr[*i - 1], i, len, &spec);
	flag = ft_check_flag(f_ptr, i);
	if (((f_ptr[*i] >= '0' && f_ptr[*i] <= '9') || f_ptr[*i] == '-' ||
		f_ptr[*i] == '.' || f_ptr[*i] == '*' || f_ptr[*i] == ' ' ||
		f_ptr[*i] == '+' || f_ptr[*i] == '#') && spec.specifier != 0)
		ft_check_flags(f_ptr, i, &spec, ap);
	if (f_ptr[*i] != '\0')
	{
		if ((spec.specifier != 2 && (flag != 2)) || (flag == 2 &&
			spec.specifier == 0))
			ft_putchar(f_ptr[*i], len);
	}
	if ((flag && flag != 2) || spec.specifier != 0)
	{
		ft_numbers(f_ptr[*i], len, &spec, ap);
		ft_char(f_ptr[*i], len, &spec, ap);
		ft_string(f_ptr[*i], len, &spec, ap);
		ft_hexidecimal_pointer(f_ptr[*i], len, &spec, ap);
	}
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	const char	*f_ptr;
	int			i;
	int			len;

	va_start(ap, format);
	i = 0;
	len = 0;
	f_ptr = format;
	while (f_ptr[i] != '\0')
	{
		if (f_ptr[i] != '%')
			ft_putchar(f_ptr[i], &len);
		else if (f_ptr[i] == '%')
			ft_parsing(f_ptr, &i, &len, ap);
		if (f_ptr[i] != '\0')
			i++;
	}
	if (f_ptr[i] == '\0')
	{
		va_end(ap);
		return (len);
	}
	va_end(ap);
	return (-1);
}
