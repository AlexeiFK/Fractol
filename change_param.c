
#include <pthread.h>
#include "fractol.h"
#include "mlx.h"
#include "config.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h> //
#include <math.h>

void	change_pres(t_param *param, int pres)
{
	char	*pres_info;

	if (param->current_fractal == MAND_SMOOTH)
		free_palette(param->palette, param->pres * SMOOTH_EXTRA_PAL);
	else
		free_palette(param->palette, param->pres);
	param->pres += pres;
	pres_info = ft_itoa(param->pres);
	mlx_string_put(param->mlx_ptr, param->win_ptr, 0, 0, 0xffffff, pres_info);
	free(pres_info);
//	printf("pres = %d\n", param->pres); //put on screen
	if (param->current_fractal == MAND_SMOOTH)
		param->palette = new_palette(param->pres * SMOOTH_EXTRA_PAL, param->color_scheme);
	else
		param->palette = new_palette(param->pres, param->color_scheme);
}

void	shift_set(t_param *param, long double x, long double y)
{
	param->start_x += x;
	param->start_y += y;
}

void	shift_setj(t_param *param, long double x, long double y)
{
	param->j_start_x += x;
	param->j_start_y += y;
}

void	change_n(t_param *param, int n)
{
	if (n > 0 && param->n < MULTI_POWER_MAX)
		param->n += n;
	else if (n < 0 && param->n > MULTI_POWER_MIN)
		param->n += n;
}

void	zoom_mand(t_param *param, long double mult, long double x, long double y)
{
	long double		res1;
	long double		res2;

	res1 = (param->start_x - x) * mult;
	res2 = (param->start_y - y) * mult;
	param->start_x = x + res1;
	param->start_y = y + res2;
	param->mult = param->mult * mult;
}
