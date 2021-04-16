
NAME = miniRT

HEADER = includes

FOLDER = srcs

SRCS_LIST = minirt.c parse_rt.c \
			errors.c hooks.c \
			drawing.c vec.c vec2.c \
			trace_ray.c \
			rotation.c sphere.c \
			lights.c utils.c \
			bmp.c colors.c \
			cylinder.c parse_elements.c \
			parse_objs.c camera.c direction.c

SRCS = $(addprefix ${FOLDER}/, ${SRCS_LIST})

OBJS = $(SRCS:.c=.o)

LIBFT 			= libft

MLX 			= minilibx

CC				= gcc -Wall -Wextra -Werror
CFLAGS 			=
LFLAGS			= -L libft -lft

METAL_MLX		= libmlx.dylib -framework Metal -framework AppKit

RM				= rm -f

all:			$(NAME)

test:
	@make -s -C $(LIBFT)
	mv libft/libft.a ./
	${CC} ${CFLAGS} ${SRCS} -I ${HEADER} libft.a

$(NAME):		$(OBJS)
				@make -s -C $(MLX)
				@mv $(MLX)/libmlx.dylib .
				@make -s -C $(LIBFT)
				@$(CC) $(CFLAGS) $(LFLAGS) $(METAL_MLX) -I $(HEADER) $(OBJS) -o $(NAME)

%.o: %.c
				@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<

clean:
				@$(RM) $(OBJS)
				@make clean -C $(MLX)
				@make clean -C $(LIBFT)

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) libmlx.dylib
				@make fclean -C $(LIBFT)

re:				fclean all

.PHONY: 		all fclean clean re