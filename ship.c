/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:01:38 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/12 21:21:22 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "config.h"
#include <stdlib.h>
#include <math.h>

static int		to_iterate(long double c_x, long double c_y, int i, int i_max)
{
	long double	x;
	long double	y;
	long double	xx;
	long double	yy;
	long double	xy2;

	c_y = -c_y;
	x = 0;
	y = 0;
	xx = 0;
	yy = 0;
	xy2 = 0;
	while (i < i_max && ((xx + yy) <= 4.0))
	{
		y = fabsl(y);
		x = fabsl(x);
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

static void		check_pixel(t_param *param,
		long double xd, long double yd, int i_max)
{
	long double	c_x;
	long double	c_y;
	int			i;

	c_x = ((param->start_x) - xd) / param->mult;
	c_y = (yd - (param->start_y)) / param->mult;
	i = 0;
	i = to_iterate(c_x, c_y, i, i_max);
	ch_pixel_put(param, xd, yd, param->palette[i]);
}

void			*trd_func_ship(void *p)
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
			check_pixel(param, x, y, pres);
			y += 1;
		}
		x += THREADS_NUM;
	}
	return (NULL);
}
