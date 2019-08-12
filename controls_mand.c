/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_mand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 16:30:17 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/12 20:16:07 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"
#include "config.h"
#include "keys.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int		keyboard_f(int keycode, void *param)
{
	if (keycode == EKEY)
		change_color(param);
	if (keycode == RKEY)
		random_color(param);
	if (keycode == ZKEY)
		change_pres(param, SENS_PRES);
	if (keycode == XKEY)
		change_pres(param, -SENS_PRES);
	if (keycode == WKEY)
		change_n(param, -1);
	if (keycode == QKEY)
		change_n(param, 1);
	if (keycode == ARROW_L)
		shift_set(param, SENS_HOR, 0);
	if (keycode == ARROW_R)
		shift_set(param, -SENS_HOR, 0);
	if (keycode == ARROW_U)
		shift_set(param, 0, SENS_VERT);
	if (keycode == ARROW_D)
		shift_set(param, 0, -SENS_VERT);
	if (keycode == ESC)
		free_and_exit(param);
	calc_and_refresh(param);
	return (0);
}

int		mouse_f(int buttom, int x, int y, void *param)
{
	static int	i = 0;

	if (buttom == 5 && i > MIN_ZOOM)
	{
		i--;
		zoom_mand(param, SENS_ZOOM_OUT, x, y);
	}
	if (buttom == 4 && i < MAX_ZOOM)
	{
		i++;
		zoom_mand(param, SENS_ZOOM_IN, x, y);
	}
	calc_and_refresh(param);
	return (0);
}
