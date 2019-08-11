
#include "fractol.h"
#include "mlx.h"
#include <stdio.h>
#include <pthread.h>

static int	to_iterate(long double s_x, long double s_y, int i, t_param *p)
{
	long double	x;	
	long double	y;
	long double	xx;	
	long double	yy;
	long double	xy2;

	x = s_x;
	y = s_y;
	xx = x * x;
	yy = y * y;
	xy2 = 0;
	while (i < p->pres && ((xx + yy) <= 4.0))
	{
		xx = x * x;
		yy = y * y;
		xy2 = x * y;
		xy2 += xy2;
		y = xy2 + p->julia_y;
		x = xx - yy + p->julia_x;
		++i;
	}
	return (i);
}

static void	check_pixel(t_param *param, long double xd, long double yd) //long double *new_x, long double *new_y)
{
	long double	c_x;	
	long double	c_y;
	int		i;

	c_x = ((param->j_start_x) - xd) / param->j_mult;
	c_y = (yd - (param->j_start_y)) / param->j_mult;
	i = 0;
	i = to_iterate(c_x, c_y, i, param);
	ch_pixel_put(param, xd, yd, param->palette[i]);
}

void		*trd_func_julia(void *p)
{
	int		x;
	int		y;
	t_param		*param;
	t_thread_param	*thread_param;

	thread_param = (t_thread_param*)p;
	param = (t_param*)(thread_param->p);
	x = thread_param->pixel_start;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGTH)
		{
			check_pixel(param, x, y);
			y += 1;
		}
		x += THREADS_NUM;
	}
	return (NULL);
}

void	create_j(t_param *param, long double mult, long double x, long double y)
{
	param->mult = param->mult * mult;
	param->julia_x = ((param->start_x) - x) / param->mult;
	param->julia_y = (y - (param->start_y)) / param->mult;
}

void	print_j(t_param *param, long double mult, long double x, long double y)
{
	long double		res1;
	long double		res2;

	res1 = (param->j_start_x - x) * mult;
	res2 = (param->j_start_y - y) * mult;
	param->j_start_x = x + res1;
	param->j_start_y = y + res2;
	param->j_mult = param->j_mult * mult;
}
