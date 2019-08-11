
#include <pthread.h>
#include "fractol.h"
#include "mlx.h"
#include "config.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>
/*
void	check_pixel_big(t_param *param, long double xd, long double yd, int i_max) //long double *new_x, long double *new_y)
{
//	long double	c_x;	
//	long double	c_y;
	int		i;
//	t_spec		spec;

	c_x = ((param->start_x) - xd) / param->mult;
	c_y = (yd - (param->start_y)) / param->mult;
	i = 0;
//	i = to_iterate(c_x, c_y, i, i_max);
	ch_pixel_put(param, xd, yd, param->palette[i]);
//	ch_pixel_put(param, xd + 1, yd, param->palette[i]);
//	ch_pixel_put(param, xd, yd + 1, param->palette[i]);
//	ch_pixel_put(param, xd + 1, yd + 1, param->palette[i]);
}*/

/*
void	*trd_func_big(void *p)
{
	int		x;
	int		y;
	int		pres;
	t_param		*param;
	t_thread_param	*thread_param;

	thread_param = (t_thread_param*)p;
	param = (t_param*)(thread_param->p);
	pres = param->pres;
	x = thread_param->pixel_start * 2;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGTH)
		{
			check_pixel_big(param, x, y, pres);
			y += 2;
		}
		x += (THREADS_NUM * 2);
	}
	return (NULL);
}

void	*trd_func_chess(void *p)
{
	int		x;
	int		y;
	int		y_start;
	int		pres;
	t_param		*param;
	t_thread_param	*thread_param;

	thread_param = (t_thread_param*)p;
	param = (t_param*)(thread_param->p);
	x = thread_param->pixel_start;// * 2;
	if (x % 2 == 0)
		y_start = 0;
	else
		y_start = 1;
	while (x < WINDOW_WIDTH)
	{
		y = y_start;
		while (y < WINDOW_HEIGTH)
		{
			check_pixel_big(param, x, y, param->pres);
			y += 2;
		}
		x += (THREADS_NUM);
	}
	return (NULL);
}
*/
