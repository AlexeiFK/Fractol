/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smooth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:52:36 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/26 11:06:24 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "config.h"
#include <stdlib.h>
#include <math.h>

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
	int	temp;

	temp = floor(i * SMOOTH_EXTRA_PAL);
	if (temp < 0 || temp > (i_max * SMOOTH_EXTRA_PAL))
		return ;
	s->r = param->palette[temp]->r;
	s->g = param->palette[temp]->g;
	s->b = param->palette[temp]->b;
}

void	check_pixel_smooth(t_param *param,
		long double xd, long double yd, int i_max)
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

void	*trd_func_smooth(void *p)
{
	int				x;
	int				y;
	int				pres;
	t_param			*param;
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
