

#include <stdlib.h>
//#include "libft.h"
#include "fractol.h"
#include "mlx.h"

static void	mlx_setup(t_param *param)
{
	int	bits;
	int	endian;

	param->mlx_ptr = mlx_init();
	param->win_ptr = mlx_new_window(param->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGTH, W_NAME);
	param->img_ptr = mlx_new_image(param->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGTH);
	param->start_x = WINDOW_W_C;
	param->start_y = WINDOW_H_C;
	param->pres = 255;
	param->k = 100;
	param->k1 = 1;
	param->k2 = 1;
	param->k3 = 1;
	param->mult = -300;
	param->s = mlx_get_data_addr(param->img_ptr, &bits, &(param->size), &endian);
}

static void	usage_msg(void)
{
//	ft_putstr("usage: \n");
	exit(0);
}

int		main(int argc, char **argv)
{
	t_param 	param;

	mlx_setup(&param);
	mlx_key_hook(param.win_ptr, keyboard_f, (void*)(&param));
	mlx_mouse_hook(param.win_ptr, mouse_f, (void*)(&param));
//	mlx_loop_hook(param.mlx_ptr, hook_f, (void*)(&param));
	mlx_loop(param.mlx_ptr);
	return (0);
}
