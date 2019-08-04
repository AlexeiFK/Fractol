
#include <pthread.h>
#include "fractol.h"
#include "mlx.h"
#include "config.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>

void	trd_starter(t_param *param, void *(*func)(void*))
{
	pthread_t	t[THREADS_NUM];
	t_thread_param	p[THREADS_NUM];
	int		i;

	i = 0;
	while (i < THREADS_NUM)
	{
		p[i].pixel_start = i;
		p[i].p = param;
		pthread_create(&t[i], NULL, func, &p[i]);
		i++;
	}
	i = 0;
	while (i < THREADS_NUM)
	{
		pthread_join(t[i], NULL);
		i++;
	}
//	upscale(param);
///	chess_scale(param);
       	// errors
}

void	x_y_convert(t_param *param, long double xd, long double yd) //long double *new_x, long double *new_y)
{
	long double	new_x;	
	long double	new_y;
	long double	xx;
	long double	yy;

	new_x = ((param->start_x) - xd) / param->mult;
	new_y = (yd - (param->start_y)) / param->mult;
	xx = new_x * new_x;
	yy = new_y * new_y;
	printf("xx = %.50Lf, yy = %.50Lf\n", xx, yy);
	printf("x = %.50Lf, y = %.50Lf, mult = %Le\n", new_x, new_y, param->mult);
}

void	ch_pixel_put(t_param *param, int x, int y, t_spec *c)
{
	unsigned char	*s;

	s = param->s;
	s += (param->size * y);
	s[x * 4] = c->b;
	s[x * 4 + 1] = c->g;
	s[x * 4 + 2] = c->r;
}

void	calc_and_refresh(t_param *param)
{
	trd_starter(param, param->fractal_func);
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img_ptr, 0, 0); // destroy and yatayatayta
	if (param->current_fractal == MAND_CHESS)
		chess_scale(param);
}
