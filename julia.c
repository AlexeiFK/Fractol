
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

void		*trd_funcj(void *p)
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

void	m_julia(t_param *param)
{
	pthread_t	t[THREADS_NUM];
	t_thread_param	p[THREADS_NUM];
	int		i;

	i = 0;
	while (i < THREADS_NUM)
	{
		p[i].pixel_start = i;
		p[i].p = param;
		pthread_create(&t[i], NULL, trd_funcj, &p[i]);
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

void	change_pres_j(t_param *param, int pres)
{
	free_palette(param->palette, param->pres);
	param->pres += pres;
	printf("pres = %d\n", param->pres);
	param->palette = new_palette(param->pres, param->color_scheme);
}
void	random_color_j(t_param *param)
{
	free_palette(param->palette, param->pres);
	param->palette = new_palette(param->pres, RANDOM_SCHEME);
}

void	change_color_j(t_param *param)
{
	param->color_scheme += 1;
	if (param->color_scheme >= COLOR_SCHEME_MAX)
	{
		param->color_scheme = 0;
	}
	free_palette(param->palette, param->pres);
	param->palette = new_palette(param->pres, param->color_scheme);
}

void	create_j(t_param *param, long double mult, long double x, long double y)
{
	long double		res1;
	long double		res2;

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
