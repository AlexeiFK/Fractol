
#include <pthread.h>
#include "fractol.h"
#include "mlx.h"
#include "config.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>

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

int	to_iterate(long double c_x, long double c_y, int i, int i_max)
{
	long double	x;	
	long double	y;
	long double	xx;	
	long double	yy;
	long double	xy2;

	x = 0;
	y = 0;
	xx = 0;
	yy = 0;
	xy2 = 0;
	while (i < i_max && ((xx + yy) <= 4.0))
	{
		xx = x * x;
		yy = y * y;
		xy2 = x * y;
		xy2 += xy2;
		y = xy2 + c_y;
		x = xx - yy + c_x;
		++i;
	}
	return (i);
}

void	check_pixel(t_param *param, long double xd, long double yd, int i_max) //long double *new_x, long double *new_y)
{
	long double	c_x;	
	long double	c_y;
	int		i;
	t_spec		spec;

	c_x = ((param->start_x) - xd) / param->mult;
	c_y = (yd - (param->start_y)) / param->mult;
	i = 0;
	i = to_iterate(c_x, c_y, i, i_max);
	ch_pixel_put(param, xd, yd, param->palette[i]);
}

float	to_iterate_smooth(long double c_x, long double c_y, int i, int i_max)
{
	long double	x;	
	long double	y;
	long double	xx;	
	long double	yy;
	long double	xy2;

	x = 0;
	y = 0;
	xx = 0;
	yy = 0;
	xy2 = 0;
	while (i < i_max && ((xx + yy) <= SMOOTH_ESCAPE))
	{
		xx = x * x;
		yy = y * y;
		xy2 = x * y;
		xy2 += xy2;
		y = xy2 + c_y;
		x = xx - yy + c_x;
		i += 1.0;
	}
	if (i == i_max)
		return (i);
	return (i - log2(log2(xx + yy)) + 4.0);
}

void	get_smooth_color(float i, float i_max, t_spec *s, t_param *param)
{
	int	i_up;
	int	i_down;
	int	temp;
	t_spec	*up;
	t_spec	*down;

	temp = floor(i * SMOOTH_EXTRA_PAL);
	if (temp < 0 || temp > (i_max * SMOOTH_EXTRA_PAL))
		return ;
	s->r = param->palette[temp]->r;
	s->g = param->palette[temp]->g;
	s->b = param->palette[temp]->b;
}

void	check_pixel_smooth(t_param *param, long double xd, long double yd, int i_max) //long double *new_x, long double *new_y)
{
	long double	c_x;	
	long double	c_y;
	float		i;
	t_spec		spec;

	c_x = ((param->start_x) - xd) / param->mult;
	c_y = (yd - (param->start_y)) / param->mult;
	i = 0;
	i = to_iterate_smooth(c_x, c_y, i, i_max);
	get_smooth_color(i, i_max, &spec, param);
	ch_pixel_put(param, xd, yd, &spec);
}

void	check_pixel_big(t_param *param, long double xd, long double yd, int i_max) //long double *new_x, long double *new_y)
{
	long double	c_x;	
	long double	c_y;
	int		i;
	t_spec		spec;

	c_x = ((param->start_x) - xd) / param->mult;
	c_y = (yd - (param->start_y)) / param->mult;
	i = 0;
	i = to_iterate(c_x, c_y, i, i_max);
	ch_pixel_put(param, xd, yd, param->palette[i]);
//	ch_pixel_put(param, xd + 1, yd, param->palette[i]);
//	ch_pixel_put(param, xd, yd + 1, param->palette[i]);
//	ch_pixel_put(param, xd + 1, yd + 1, param->palette[i]);
}

void	biliner_put_4dots(t_param *param, int x, int y)
{
	unsigned char	*sm;
	unsigned char	*sp;
	unsigned char	*sn;
	int		temp;

	sp = param->s;
	sp += (param->size * (y - 1));
	sn = param->s;
	sn += (param->size * (y + 1));
	sm = param->s;
	sm += (param->size * y);
	temp = (sp[x * 4] + sn[x * 4] + sm[(x + 1) * 4] + sm[(x - 1) * 4]) / 4;
	sm[x * 4] = temp;
	temp = (sp[x * 4 + 1] + sn[x * 4 + 1] + sm[(x + 1) * 4 + 1] + sm[(x - 1) * 4 + 1]) / 4;
	sm[x * 4 + 1] = temp;
	temp = (sp[x * 4 + 2] + sn[x * 4 + 2] + sm[(x + 1) * 4 + 2] + sm[(x - 1) * 4 + 2]) / 4;
	sm[x * 4 + 2] = temp;
}

void	biliner_put(t_param *param, int x, int y)
{
	unsigned char	*sm;
	unsigned char	*sp;
	unsigned char	*sn;
	int		temp;

	sp = param->s;
	sp += (param->size * (y - 1));
	sn = param->s;
	sn += (param->size * (y + 1));
	sm = param->s;
	sm += (param->size * y);
	temp = (sp[x * 4] + sn[x * 4]) / 2;
	sm[x * 4] = temp;
	temp = (sp[x * 4 + 1] + sn[x * 4 + 1]) / 2;
	sm[x * 4 + 1] = temp;
	temp = (sp[x * 4 + 2] + sn[x * 4 + 2]) / 2;
	sm[x * 4 + 2] = temp;
}

void	biliner_put_hor(t_param *param, int x, int y)
{
	unsigned char	*sm;
	int		temp;

	sm = param->s;
	sm += (param->size * y);
	temp = (sm[(x + 1) * 4] + sm[(x - 1) * 4]) / 2;
	sm[x * 4] = temp;
	temp = (sm[(x + 1) * 4 + 1] + sm[(x - 1) * 4 + 1]) / 2;
	sm[x * 4 + 1] = temp;
	temp = (sm[(x + 1) * 4 + 2] + sm[(x - 1) * 4 + 2]) / 2;
	sm[x * 4 + 2] = temp;
}

void	chess_scale(t_param *param)
{
	int	x;
	int	y;
	int	y_start;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		if (x % 2 == 0)
			y = 1;
		else
			y = 0;
		while (y < WINDOW_HEIGTH)
		{
			biliner_put_4dots(param, x, y);
			y += 2;
		}
		x += 1;
	}
}
void	upscale(t_param *param)
{
	int	x;
	int	y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 1;
		while (y < WINDOW_HEIGTH)
		{
			biliner_put(param, x, y);
			y += 2;
		}
		x += 2;
	}
	x = 1;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGTH)
		{
			biliner_put_hor(param, x, y);
			y += 2;
		}
		x += 2;
	}
	x = 1;
	while (x < WINDOW_WIDTH)
	{
		y = 1;
		while (y < WINDOW_HEIGTH)
		{
			biliner_put(param, x, y);
			y += 2;
		}
		x += 2;
	}
}

void	*trd_func(void *p)
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

void	*trd_func_smooth(void *p)
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
			check_pixel_smooth(param, x, y, pres);
			y += 1;
		}
		x += THREADS_NUM;
	}
	return (NULL);
}
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

void	change_pres(t_param *param, int pres)
{
	free_palette(param->palette, param->pres);
	param->pres += pres;
	printf("pres = %d\n", param->pres);
	param->palette = new_palette(param->pres, param->color_scheme);
}

void	random_color(t_param *param)
{
	free_palette(param->palette, param->pres);
	param->color_scheme = RANDOM_SCHEME;
	param->palette = new_palette(param->pres, RANDOM_SCHEME);
}

void	change_color(t_param *param)
{
	param->color_scheme += 1;
	if (param->color_scheme >= COLOR_SCHEME_MAX)
	{
		param->color_scheme = 0;
	}
	free_palette(param->palette, param->pres);
	param->palette = new_palette(param->pres, param->color_scheme);
}

void	shift_set(t_param *param, long double x, long double y)
{
	param->start_x += x;
	param->start_y += y;
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
}
