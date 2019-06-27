

#include "mlx.h"
#include "fractol.h"
#include "config.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int		keyboard_fj(int keycode, void *param)
{
//	printf("_______________________________%d\n", keycode);
	if (keycode == QKEY)
		print(param, 1, WINDOW_WIDTH, WINDOW_HEIGTH);
	//	change_color_par(param, 0, 0, 1);
	if (keycode == WKEY)
		change_color_par(param, 0, 1, 0);
	if (keycode == EKEY)
		change_color_par(param, 1, 0, 0);
	if (keycode == AKEY)
		change_color_par(param, 0, 0, -1);
	if (keycode == SKEY)
		change_color_par(param, 0, -1, 0);
	if (keycode == DKEY)
		change_color_par(param, -1, 0, 0);
	if (keycode == ZKEY)
		change_pres(param, 10);
	if (keycode == XKEY)
		change_pres(param, -10);
	if (keycode == ESC)
		exit(0);
	return (0);
}

int		mouse_fj(int buttom, int x, int y, void *param)
{
	static int	i = 0;
	if (buttom == 1)
	{
		printf("i = %d\n", i);
		x_y_convert(param, x, y);
	}
	if (buttom == 3)
	{
		create_j(param, 1, x, y);
	}
	if (buttom == 5)
	{
		i--;
		print_j(param, 0.9, x, y);
	}
	if (buttom == 4)
	{
		i++;
		print_j(param, 1.1, x, y);
	}
	return (0);
}

int		keyboard_f(int keycode, void *param)
{
//	printf("_______________________________%d\n", keycode);
	if (keycode == QKEY)
		change_color_par(param, 0, 0, 1);
	if (keycode == WKEY)
		change_color_par(param, 0, 1, 0);
	if (keycode == EKEY)
		change_color_par(param, 1, 0, 0);
	if (keycode == AKEY)
		change_color_par(param, 0, 0, -1);
	if (keycode == SKEY)
		change_color_par(param, 0, -1, 0);
	if (keycode == DKEY)
		change_color_par(param, -1, 0, 0);
	if (keycode == ZKEY)
		change_pres(param, 10);
	if (keycode == XKEY)
		change_pres(param, -10);
	if (keycode == ARROW_D)
		shift_set(param, 0, 20);
	if (keycode == ARROW_U)
		shift_set(param, 0, -20);
	if (keycode == ARROW_R)
		shift_set(param, 20, 0);
	if (keycode == ARROW_L)
		shift_set(param, -20, 0);
	if (keycode == ESC)
		exit(0);
	return (0);
}

int		mouse_f(int buttom, int x, int y, void *param)
{
	static int	i = 0;
	if (buttom == 1)
	{
		printf("i = %d\n", i);
		x_y_convert(param, x, y);
	}
	if (buttom == 2)
	{
		change_color(param);
	}
	if (buttom == 5)
	{
		i--;
		print(param, 0.9, x, y);
	}
	if (buttom == 4)
	{
		i++;
		print(param, 1.1, x, y);
	}
	return (0);
}

int		hook_f(void *p)
{
	t_param		*param;	

	param = (t_param*)p;
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img_ptr, 0, 0); // destroy and yatayatayta
}
