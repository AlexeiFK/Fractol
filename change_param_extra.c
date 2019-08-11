/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_param_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:52:59 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/11 19:53:49 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "fractol.h"
#include "mlx.h"
#include "config.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>

void	random_color(t_param *param)
{
	param->color_scheme = RANDOM_SCHEME;
	if (param->current_fractal == MAND_SMOOTH)
	{
		free_palette(param->palette, param->pres * SMOOTH_EXTRA_PAL);
		param->palette =
			new_palette(param->pres * SMOOTH_EXTRA_PAL, RANDOM_SCHEME);
	}
	else
	{
		free_palette(param->palette, param->pres);
		param->palette = new_palette(param->pres, RANDOM_SCHEME);
	}
}

void	change_color(t_param *param)
{
	param->color_scheme += 1;
	if (param->color_scheme >= COLOR_SCHEME_MAX)
	{
		param->color_scheme = 0;
	}
	if (param->current_fractal == MAND_SMOOTH)
	{
		free_palette(param->palette, param->pres * SMOOTH_EXTRA_PAL);
		param->palette =
			new_palette(param->pres * SMOOTH_EXTRA_PAL, param->color_scheme);
	}
	else
	{
		free_palette(param->palette, param->pres);
		param->palette = new_palette(param->pres, param->color_scheme);
	}
}

void	shift_julia_param(t_param *param, long double x, long double y)
{
	param->julia_x += x;
	param->julia_y += y;
}
