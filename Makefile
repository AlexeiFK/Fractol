
NAME = fractol

#FLAGS = -Wall -Wextra -Werror

#FLAGS = -Ofast -mtune=native -march=native -mfpmath=sse -funroll-loops -funroll-all-loops -ffast-math -fforce-addr
FLAGS = -march=native -Ofast -pipe -Wall -Wextra -Werror

LIBFT = -L libft/ -lft

MINILIB = -L minilibx_macos/ -lmlx

#FRAMEW = -framework OpenGL -framework Appkit

CFILES = main.c controls.c print.c julia.c palette.c color_scheme.c ship.c tricorn.c multibrot.c multijulia.c \
	 change_param.c change_param_extra.c misc.c mand.c smooth.c upscale.c exit.c setup.c

OBJ = $(CFILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) fractol.h config.h keys.h colors.h
	make -C libft
	gcc $(FLAGS) $(OBJ) -o $(NAME) -lm -Iminilibx/include -lbsd $(pkg-config --libs libbsd) $(LIBFT) -L/usr/X11/lib /usr/X11/lib/libmlx.a -lbsd -lXext -lbsd -lX11 -lbsd -lpthread

$(OBJ): $(CFILES) fractol.h config.h keys.h colors.h
	gcc $(FLAGS) -c $(CFILES) -lm -Ilibft -Iminilibx_macos

clean:
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
