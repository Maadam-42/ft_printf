/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 13:25:27 by maadam            #+#    #+#             */
/*   Updated: 2020/07/16 13:25:27 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct
{
	int			minus;
	int			plus;
	int			nul;
	int			hex_nul;
	int			width;
	int			width_star;
	int			dot;
	int			dot_was;
	int			precision;
	int			precision_star;
	int			pre_was_min;
	int			pre_for_hex;
	int			space;
	int			octotorp;
	int			num_was_min;
	int			specifier;
	int			flag_for_some;
	int			percent;
	char		p_char;
	int			size;
}				t_flags;

int				ft_printf(const char *format, ...);
void			ft_putchar(char c, int *len);
int				ft_toupper(int ch);
void			ft_bzero(void *s, size_t n);
void			ft_check_struct(t_flags *spec);
void			ft_putstr(const char *str, int str_len, int *len,
							t_flags *spec);
int				ft_check_flag(const char *f_ptr, int *i);
int				ft_hex_point_len(unsigned long int number);
int				ft_strlen(const char *str);
int				ft_atoi(const char *f_ptr, int *i, t_flags *spec);
void			ft_numbers(const char ch, int *len, t_flags *spec, va_list ap);
void			ft_print_num_width(long long *number, int num_len,
									int *len, t_flags *spec);
void			ft_print_num_precision(long long *number, int num_len,
										int *len, t_flags *spec);
void			ft_char(const char ch, int *len, t_flags *spec, va_list ap);
void			ft_string(const char ch, int *len,
								t_flags *spec, va_list ap);
void			ft_hexidecimal_pointer(const char ch, int *len,
										t_flags *spec, va_list ap);
void			ft_print_hex_width_part_one(int *num_len, int *len,
											t_flags *spec);
void			ft_print_num_space_nul(long long int *number, int num_len,
										int *len, t_flags *spec);
void			ft_print_num_space(int *len, t_flags *spec);
void			ft_print_hex_precision(int *num_len, int *len, t_flags *spec);
void			ft_print_null_pointer(int *len, t_flags *spec);
void			ft_print_hexidecimal(unsigned long int number,
										int *len, t_flags *spec);

#endif
