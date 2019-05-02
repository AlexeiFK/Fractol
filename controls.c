

#include "mlx.h"
#include "fractol.h"
#include "config.h"
#include <math.h>
#include <stdlib.h>

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
	if (keycode == ESC)
		exit(0);
	return (0);
}

int		mouse_f(int buttom, int x, int y, void *param)
{
	if (buttom == 1)
	{
		x_y_convert(param, x, y);
	}
	if (buttom == 2)
	{
		change_color(param);
	}
	if (buttom == 5)
	{
		print(param, 0.9, x, y);
	}
	if (buttom == 4)
	{
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
