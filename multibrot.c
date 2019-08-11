/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multibrot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:10:50 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/11 19:10:54 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "fractol.h"
#include "mlx.h"
#include "config.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>

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

static void	check_pixel(t_param *param, long double xd, long double yd)
{
	long double	c_x;
	long double	c_y;
	int			i;

	c_x = ((param->start_x) - xd) / param->mult;
	c_y = (yd - (param->start_y)) / param->mult;
	i = 0;
	i = to_iterate(c_x, c_y, i, param);
	ch_pixel_put(param, xd, yd, param->palette[i]);
}

void		*trd_func_multibrot(void *p)
{
	int				x;
	int				y;
	t_param			*param;
	t_thread_param	*thread_param;

	thread_param = (t_thread_param*)p;
	param = (t_param*)(thread_param->p);
	x = thread_param->pixel_start;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGTH)
		{
			check_pixel(param, x, y);
			y += 1;
		}
		x += THREADS_NUM;
	}
	return (NULL);
}
