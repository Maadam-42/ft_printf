# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/28 13:13:46 by maadam            #+#    #+#              #
#    Updated: 2020/07/28 13:13:46 by maadam           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc

FLAGS = -Wall -Werror -Wextra

HEADER = ft_printf.h

SRCS =	ft_printf.c ft_printf_utils.c ft_print_char.c ft_print_number.c \
		 ft_print_number_flags.c ft_print_hexidecimal.c \
		 ft_printf_utils_part_two.c ft_print_hexidecimal_flags.c \
		 ft_print_string.c ft_print_number_flags_if.c \
		 ft_print_hexidecimal_part_two.c

OBJS := $(patsubst %.c, %.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $(OBJS)
	ranlib $(NAME)

%.o:%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean
