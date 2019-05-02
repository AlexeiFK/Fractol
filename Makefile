
NAME = fractol

#FLAGS = -Wall -Wextra -Werror

FLAGS = -O2

LIBFT = -L libft/ -lft

MINILIB = -L minilibx_macos/ -lmlx

#FRAMEW = -framework OpenGL -framework Appkit

CFILES = main.c controls.c print.c

OBJ = $(CFILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) fractol.h config.h
	make -C libft
	gcc $(FLAGS) $(OBJ) -o $(NAME) -lm -Iminilibx/include -lbsd $(pkg-config --libs libbsd) $(LIBFT) -L/usr/X11/lib /usr/X11/lib/libmlx.a -lbsd -lXext -lbsd -lX11 -lbsd

$(OBJ): $(CFILES) fractol.h config.h
	gcc $(FLAGS) -c $(CFILES) -lm -Ilibft -Iminilibx_macos

clean:
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
