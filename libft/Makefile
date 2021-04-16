# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qrigil <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/13 00:15:20 by qrigil            #+#    #+#              #
#    Updated: 2020/11/13 00:15:25 by qrigil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_putnbr_fd.c ft_atoi.c \
	   ft_isalpha.c ft_calloc.c \
	   ft_isalnum.c ft_bzero.c \
	   ft_isascii.c ft_memccpy.c \
	   ft_isdigit.c ft_memchr.c \
	   ft_isprint.c ft_memcmp.c \
	   ft_itoa.c ft_memcpy.c \
	   ft_split.c ft_memmove.c \
	   ft_substr.c ft_memset.c \
	   ft_tolower.c ft_memcpy.c \
	   ft_toupper.c ft_strdup.c \
	   ft_putchar_fd.c ft_strjoin.c \
	   ft_putendl_fd.c ft_strlcat.c \
	   ft_putnbr_fd.c ft_strlcpy.c \
	   ft_putstr_fd.c ft_strlen.c \
	   ft_strchr.c ft_strmapi.c \
	   ft_strncmp.c ft_strtrim.c \
	   ft_strnstr.c ft_strrchr.c \
	   ft_strcmp.c


SRCSB = ft_lstnew.c	ft_lstadd_front.c \
		ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c \
		ft_lstclear.c	ft_lstiter.c \
		ft_lstmap.c \
		get_next_line.c get_next_line_utils.c

OBJS = ${SRCS:.c=.o}

OBJSB = ${SRCSB:.c=.o}

HEADER = includes

CC = gcc

FT_PRINTF = ft_printf
CFLAGS = -Wextra -Wall -Werror

all:		${NAME}

$(NAME):	${OBJS} ${OBJSB}
	@make -C ${FT_PRINTF}
	@cp ${FT_PRINTF}/libftprintf.a ./${NAME}
	@ar -rcs ${NAME} ${OBJS} ${OBJSB}

%.o: %.c
			@${CC} -c ${CFLAGS} -o $@ $< -I ${HEADER}

clean:
	rm -f ${OBJS} ${OBJSB}
	@make clean -C $(FT_PRINTF)

fclean: clean
	rm -f ${NAME}
	@make fclean -C $(FT_PRINTF)

re: fclean all

.PHONY: 	all fclean clean re