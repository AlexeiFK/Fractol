# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/24 22:32:32 by rjeor-mo          #+#    #+#              #
#    Updated: 2019/10/24 22:33:06 by rjeor-mo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fractol

VPATH=./

CC=gcc

LIBFT= -L libft/ -lftprintf

IDIR=./libft

MINILIB = -L minilibx_macos/ -lmlx

FRAMEW = -framework OpenGL -framework Appkit

INCLUDES= -I$(IDIR) -Iminilibx_macos/include 

HEADERS= fractol.h config.h keys.h

SRC= main.c controls_mand.c controls_julia.c \
	 julia.c palette.c color_scheme.c \
	 ship.c tricorn.c multibrot.c multijulia.c \
	 change_param.c change_param_julia.c change_param_extra.c c_power.c \
	 mand.c smooth.c upscale.c exit.c setup.c \
	 color_funcs.c trd_start.c image.c fractal_to_fdf.c

CFLAGS= -Wall -Wextra -Werror $(INCLUDES) -O3 -march=native

RM= rm -f

all: $(NAME)

OBJ=$(SRC:.c=.o)

$(NAME): $(OBJ) $(HEADERS)
	make -C libft
	make -C minilibx_macos
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(FRAMEW) $(MINILIB) -lpthread 
	@echo "Fractol ready."

%.o: %.c $(HEADERS)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	$(RM) $(OBJ)
	make clean -C libft
	make clean -C minilibx_macos

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all
