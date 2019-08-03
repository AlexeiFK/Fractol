
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
	while (i < p->pres && ((x * x + y * y) <= 4.0))
	{
		c_power(&x, &y, p->n);
		y = y + p->julia_y;
		x = x + p->julia_x;
		++i;
	}
	return (i);
}

static void	check_pixel(t_param *param, long double xd, long double yd, int i_max) //long double *new_x, long double *new_y)
{
	long double	c_x;	
	long double	c_y;
	int		i;
	t_spec		spec;

	c_x = ((param->j_start_x) - xd) / param->j_mult;
	c_y = (yd - (param->j_start_y)) / param->j_mult;
	i = 0;
	i = to_iterate(c_x, c_y, i, param);
	ch_pixel_put(param, xd, yd, param->palette[i]);
}

void	*trd_func_multijulia(void *p)
{
	int		x;
	int		y;
	int		pres;
	t_param		*param;
	t_thread_param	*thread_param;

	thread_param = (t_thread_param*)p;
	param = (t_param*)(thread_param->p);
	pres = param->pres;
	x = thread_param->pixel_start;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGTH)
		{
			check_pixel(param, x, y, pres);
			y += 1;
		}
		x += THREADS_NUM;
	}
	return (NULL);
}
