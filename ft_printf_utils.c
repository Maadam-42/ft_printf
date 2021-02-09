/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 17:29:53 by maadam            #+#    #+#             */
/*   Updated: 2020/07/22 17:29:53 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}

int		ft_toupper(int ch)
{
	if (ch >= 97 && ch <= 122)
		return (ch - 32);
	return (ch);
}

int		ft_hex_point_len(unsigned long int number)
{
	int i;

	i = 1;
	while (number >= 16)
	{
		number /= 16;
		i++;
	}
	return (i);
}

int		ft_strlen(const char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int		ft_atoi(const char *f_ptr, int *i, t_flags *spec)
{
	int	min;
	int	res;

	min = 1;
	res = 0;
	while (f_ptr[*i] == ' ' || f_ptr[*i] == '\t' || f_ptr[*i] == '\n' ||
			f_ptr[*i] == '\v' || f_ptr[*i] == '\f' || f_ptr[*i] == '\r')
		(*i)++;
	if (f_ptr[*i] == '-' || f_ptr[*i] == '+')
	{
		if (f_ptr[*i] == '-')
			min = -1;
		(*i)++;
	}
	while (f_ptr[*i] >= '0' && f_ptr[*i] <= '9')
	{
		res = res * 10 + (f_ptr[*i] - '0');
		(*i)++;
	}
	if (f_ptr[*i] == '.')
	{
		spec->dot = 1;
		(*i)++;
	}
	return (res * min);
}
