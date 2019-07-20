
#include "fractol.h"
#include "mlx.h"
#include <pthread.h>

static int	to_iterate(long double s_x, long double s_y, int i, int i_max, long double c_x, long double c_y)
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

static void	check_pixel(t_param *param, long double xd, long double yd, int i_max) //long double *new_x, long double *new_y)
{
	long double	c_x;	
	long double	c_y;
	int		i;
	t_spec		spec;

	c_x = ((param->j_start_x) - xd) / param->j_mult;
	c_y = (yd - (param->j_start_y)) / param->j_mult;
	i = 0;
	i = to_iterate(c_x, c_y, i, i_max, param->julia_x, param->julia_y);
	ch_pixel_put(param, xd, yd, param->palette[i]);
}

static void	*trd_func_odd(void *p)
{
	int		x;
	int		y;
	int		pres;
	t_param		*param;

	param = (t_param*)p;
	pres = param->pres;
	x = 1;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGTH)
		{
			check_pixel(param, x, y, pres);
			y += 1;
		}
		x += 2;
	}
	return (NULL);
}

static void	*trd_func_even(void *p)
{
	int		x;
	int		y;
	int		pres;
	t_param		*param;

	param = (t_param*)p;
	pres = param->pres;
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGTH)
		{
			check_pixel(param, x, y, pres);
			y += 1;
		}
		x += 2;
	}
	return (NULL);
}

void	m_julia(t_param *param)
{
	int		x;
	int		y;
	int		pres;
	pthread_t	t1;
	pthread_t	t2;

	pthread_create(&t1, NULL, trd_func_even, param);
	pthread_create(&t2, NULL, trd_func_odd, param);
       	// errors
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
}

void	random_color_j(t_param *param)
{
	free_palette(param->palette, param->pres);
	param->palette = new_palette(param->pres, RANDOM_SCHEME);
	m_julia(param);
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img_ptr, 0, 0); // destroy and yatayatayta
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
	m_julia(param);
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img_ptr, 0, 0); // destroy and yatayatayta
}

void	create_j(t_param *param, long double mult, long double x, long double y)
{
	long double		res1;
	long double		res2;

	param->mult = param->mult * mult;
	param->julia_x = ((param->start_x) - x) / param->mult;
	param->julia_y = (y - (param->start_y)) / param->mult;
	//param->julia_x = x;
	//param->julia_y = y;
	m_julia(param);
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img_ptr, 0, 0); // destroy and yatayatayta
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
	m_julia(param);
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img_ptr, 0, 0); // destroy and yatayatayta
}
