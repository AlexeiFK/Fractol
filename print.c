
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


void	set_colors(t_param *param, int i, int i_max, t_spec *spec)
{
	spec->r = (i * param->k * param->k1) % 255;
	spec->g = (i * param->k * param->k2) % 255;
	spec->b = (i * param->k * param->k3) % 255;
}

void	set_color(t_param *param, int i, int i_max, t_spec *spec)
{
	int	k1;
	int	k2;
	int	k3;

	k1 = 0;
	k2 = 0;
	k3 = 0;
	if (i % 8 == 0)
		k1 = 1;
	else if (i % 8 == 1)
		k2 = 1;
	else if (i % 8 == 2)
		k3 = 1;
	else if (i % 8 == 3)
	{
		k1 = 1;
		k2 = 1;
	}
	else if (i % 8 == 4)
	{
		k1 = 1;
		k2 = 1;
		k3 = 1;
	}
	else if (i % 8 == 5)
	{
		k2 = 1;
		k3 = 1;
	}
	else if (i % 8 == 6)
	{
		k1 = 1;
		k3 = 1;
	}
	else if (i % 8 == 7)
		k2 = 0;
	spec->r = i * k1 * param->k1;
	spec->g = i * k2 * param->k2;
	spec->b = i * k3 * param->k3;
	if (i == i_max)
	{
		spec->r = 255;
		spec->g = 255;
		spec->b = 255;
	}
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
	set_color(param, i, i_max, &spec);
	ch_pixel_put(param, xd, yd, &spec);
}

void	*trd_func_odd(void *p)
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

void	*trd_func_even(void *p)
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

void	m_mald(t_param *param)
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

void	m_frac(t_param *param, long double mult)
{
	t_spec		spec;
	long double	x;
	long double	y;
	spec.r = 255;
	spec.g = 0;
	spec.b = 0;
}

void	change_pres(t_param *param, int pres)
{
	param->pres += pres;
	printf("pres = %d\n", param->pres);
	m_mald(param);
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img_ptr, 0, 0); // destroy and yatayatayta
}

void	change_color(t_param *param)
{
	param->k += 1;
	m_mald(param);
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img_ptr, 0, 0); // destroy and yatayatayta
}

void	change_color_par(t_param *param, int k1, int k2, int k3)
{
	param->k1 += k1;
	param->k2 += k2;
	param->k3 += k3;
	m_mald(param);
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img_ptr, 0, 0); // destroy and yatayatayta
}

void	shift_set(t_param *param, long double x, long double y)
{
	param->start_x += x;
	param->start_y += y;
	m_mald(param);
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img_ptr, 0, 0); // destroy and yatayatayta
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
	m_mald(param);
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img_ptr, 0, 0); // destroy and yatayatayta
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
