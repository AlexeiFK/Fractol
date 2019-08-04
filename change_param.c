
#include <pthread.h>
#include "fractol.h"
#include "mlx.h"
#include "config.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>

void	change_pres(t_param *param, int pres)
{
	free_palette(param->palette, param->pres);
	param->pres += pres;
	printf("pres = %d\n", param->pres);
	param->palette = new_palette(param->pres, param->color_scheme);
}

void	random_color(t_param *param)
{
	param->color_scheme = RANDOM_SCHEME;
	if (param->current_fractal == MAND_SMOOTH)
	{
		free_palette(param->palette, param->pres * SMOOTH_EXTRA_PAL);
		param->palette = new_palette(param->pres * SMOOTH_EXTRA_PAL, RANDOM_SCHEME);
	}
	else
	{
		free_palette(param->palette, param->pres);
		param->palette = new_palette(param->pres, RANDOM_SCHEME);
	}
}

void	change_color(t_param *param)
{
	param->color_scheme += 1;
	if (param->color_scheme >= COLOR_SCHEME_MAX)
	{
		param->color_scheme = 0;
	}
	if (param->current_fractal == MAND_SMOOTH)
	{
		free_palette(param->palette, param->pres * SMOOTH_EXTRA_PAL);
		param->palette = new_palette(param->pres * SMOOTH_EXTRA_PAL, param->color_scheme);
	}
	else
	{
		free_palette(param->palette, param->pres);
		param->palette = new_palette(param->pres, param->color_scheme);
	}
}

void	shift_set(t_param *param, long double x, long double y)
{
	param->start_x += x;
	param->start_y += y;
}

void	change_n(t_param *param, int n)
{
	if (n > 0 && param->n < MULTI_POWER_MAX)
		param->n += n;
	else if (n < 0 && param->n > MULTI_POWER_MIN)
		param->n += n;
}

void	print(t_param *param, long double mult, long double x, long double y)
{
	long double		res1;
	long double		res2;

	res1 = (param->start_x - x) * mult;
	res2 = (param->start_y - y) * mult;
	param->start_x = x + res1;
	param->start_y = y + res2;
	param->mult = param->mult * mult;
}
