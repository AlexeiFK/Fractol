

#include <pthread.h>
#include "fractol.h"
#include "mlx.h"
#include "config.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>

void		c_power(long double *x_o, long double *y_o, int power)
{
	long double	x;	
	long double	y;
	long double	xx;	
	long double	yy;
	int		j;

	x = *x_o;
	y = *y_o;
	j = 1;
	while (j < power)
	{
		xx = x * *x_o;
		yy = y * *y_o;
		y = x * *y_o + *x_o * y;
		x = xx - yy;
		j++;
	}
	*x_o = x;
	*y_o = y;
}


static int	to_iterate(long double c_x, long double c_y, int i, t_param *param)
{
	long double	x;	
	long double	y;

	x = 0;
	y = 0;
	while (i < param->pres && ((x * x + y * y) <= 4.0))
	{
		c_power(&x, &y, param->n);
		y = y + c_y;
		x = x + c_x;
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

	c_x = ((param->start_x) - xd) / param->mult;
	c_y = (yd - (param->start_y)) / param->mult;
	i = 0;
	i = to_iterate(c_x, c_y, i, param);
	ch_pixel_put(param, xd, yd, param->palette[i]);
}

void	*trd_func_multibrot(void *p)
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
