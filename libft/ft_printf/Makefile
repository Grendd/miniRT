# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qrigil <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/16 17:11:55 by qrigil            #+#    #+#              #
#    Updated: 2021/01/16 17:12:02 by qrigil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBFT = libft/libft.a

COMP = gcc -Wall -Werror -Wextra

HEADER = ../../includes

SRCS = 	ft_printf.c ft_print_count.c \
		ft_parse_char_percent.c ft_parse_hex.c \
		ft_parse_int.c ft_parse_string.c \
		ft_check_flags.c ft_parse_pointer.c \
		ft_parse_uint.c

OBJS = $(SRCS:.c=.o)

all: ${NAME}

${NAME}: $(OBJS) $(M_OBJS)
	@ar -rcs $(NAME) $(OBJS) $(M_OBJS)

srcs/%.o: %.c
				@${COMP} -I ${HEADER} -o $@ -c $<

clean:
	rm -f ${OBJS} ${M_OBJS} ${HEADER}.gch

fclean: clean
	rm  -f ${NAME}

re: fclean all
