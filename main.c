

#include <stdlib.h>
#include "libft.h"
#include "fractol.h"
#include "mlx.h"


static int	min_mult(int width, int height)
{
	if (width > height)
	{
		return (height / SCREEN_UNITS_W);
	}
	else
	{
		return (width / SCREEN_UNITS_W);
	}
}

static void	mlx_setup(t_param *param, int fractal)
{
	int	bits;
	int	endian;

	param->mlx_ptr = mlx_init();
	param->win_ptr = mlx_new_window(param->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGTH, W_NAME);
	param->img_ptr = mlx_new_image(param->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGTH);
	param->start_x = WINDOW_W_C;
	param->start_y = WINDOW_H_C;
	param->j_start_x = WINDOW_W_C;
	param->j_start_y = WINDOW_H_C;
	param->current_fractal = fractal;
	param->pres = 100;
	param->color_scheme = 0;
	param->palette = new_palette(param->pres, param->color_scheme);
	param->mult = min_mult(WINDOW_WIDTH - BUFFER, WINDOW_HEIGTH - BUFFER);
	param->j_mult = min_mult(WINDOW_WIDTH - BUFFER, WINDOW_HEIGTH - BUFFER);
	param->s = mlx_get_data_addr(param->img_ptr, &bits, &(param->size), &endian);
}

static void	usage_msg(void)
{
	ft_putstr("usage: ./fractol [fractal_name]\n");
	ft_putstr("fractal names:\n");
	ft_putstr("Mand = Mandelbrot set\n");
	ft_putstr("Julia = Julia set\n");
	ft_putstr("Bsf = Burning Ship Fractal\n");
	ft_putstr("Tricorn = Tricorn set\n");
	ft_putstr("MultiB = Multibrot sets\n");
	ft_putstr("MultiJ = MultiJulia sets\n");
	exit(0);
}

int		main(int argc, char **argv)
{
	t_param 	param;

	if (argc != 2)
		usage_msg();
	if (ft_strcmp(argv[1], "Mand") == 0)
	{
		mlx_setup(&param, MAND);
		mlx_key_hook(param.win_ptr, keyboard_f, (void*)(&param));
		mlx_mouse_hook(param.win_ptr, mouse_f, (void*)(&param));
		param.fractal_func = trd_func;
		calc_and_refresh(&param);
	}
	else if (ft_strcmp(argv[1], "Bsf") == 0)
	{
		mlx_setup(&param, MAND);
		mlx_key_hook(param.win_ptr, keyboard_f, (void*)(&param));
		mlx_mouse_hook(param.win_ptr, mouse_f, (void*)(&param));
		param.fractal_func = trd_func_ship;
		calc_and_refresh(&param);
	}
	else if (ft_strcmp(argv[1], "MultiB") == 0)
	{
		mlx_setup(&param, MAND);
		mlx_key_hook(param.win_ptr, keyboard_f, (void*)(&param));
		mlx_mouse_hook(param.win_ptr, mouse_f, (void*)(&param));
		param.fractal_func = trd_func_multibrot;
		param.n = 2;
		calc_and_refresh(&param);
	}
	else if (ft_strcmp(argv[1], "Tricorn") == 0)
	{
		mlx_setup(&param, MAND);
		mlx_key_hook(param.win_ptr, keyboard_f, (void*)(&param));
		mlx_mouse_hook(param.win_ptr, mouse_f, (void*)(&param));
		param.fractal_func = trd_func_tricorn;
		calc_and_refresh(&param);
	}
	else if (ft_strcmp(argv[1], "Julia") == 0)
	{
		mlx_setup(&param, JULIA_MOUSE);
		mlx_key_hook(param.win_ptr, keyboard_fj, (void*)(&param));
		mlx_mouse_hook(param.win_ptr, mouse_fj, (void*)(&param));
		mlx_hook(param.win_ptr, 6, (1L<<6), mouse_move_f, (void*)(&param));
	}
	else
		usage_msg();
	mlx_loop(param.mlx_ptr);
	return (0);
}
