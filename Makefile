
NAME = fractol

#FLAGS = -Wall -Wextra -Werror

#FLAGS = -Ofast -mtune=native -march=native -mfpmath=sse -funroll-loops -funroll-all-loops -ffast-math -fforce-addr
FLAGS = -march=native -O3 -Wall -Wextra -Werror

LIBFT = -L libft/ -lft

MINILIB = -L minilibx_macos/ -lmlx

FRAMEW = -framework OpenGL -framework Appkit

CFILES = main.c controls_mand.c controls_julia.c \
		 julia.c palette.c color_scheme.c ship.c tricorn.c multibrot.c multijulia.c \
		 change_param.c change_param_julia.c change_param_extra.c c_power.c mand.c smooth.c upscale.c exit.c setup.c \
		 color_funcs.c trd_start.c image.c fractal_to_fdf.c

OBJ = $(CFILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) fractol.h config.h keys.h colors.h
	make -C libft
	gcc $(FLAGS) $(OBJ) -o $(NAME) -lm -Iminilibx/include  $(LIBFT) $(MINILIB) $(FRAMEW) -lpthread

$(OBJ): $(CFILES) fractol.h config.h keys.h colors.h
	gcc $(FLAGS) -c $(CFILES) -Ilibft -Iminilibx_macos

clean:
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
