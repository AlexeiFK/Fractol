/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_julia.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 16:29:16 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/26 13:20:34 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "config.h"
#include "keys.h"

void	keyboard_extra(int keycode, void *param)
{
	if (keycode == PKEY)
		ft_reader(param);
	if (keycode == TKEY)
		shift_julia_param(param, 0, SENS_J);
	if (keycode == FKEY)
		shift_julia_param(param, SENS_J, 0);
	if (keycode == GKEY)
		shift_julia_param(param, 0, -SENS_J);
	if (keycode == HKEY)
		shift_julia_param(param, -SENS_J, 0);
	if (keycode == ARROW_L)
		shift_setj(param, SENS_HOR, 0);
	if (keycode == ARROW_R)
		shift_setj(param, -SENS_HOR, 0);
	if (keycode == ARROW_U)
		shift_setj(param, 0, SENS_VERT);
	if (keycode == ARROW_D)
		shift_setj(param, 0, -SENS_VERT);
	if (keycode == WKEY)
		change_n(param, -1);
	if (keycode == QKEY)
		change_n(param, 1);
}

int		keyboard_fj(int keycode, void *param)
{
	t_param		*p;

	p = (t_param*)param;
	if (keycode == RKEY)
		random_color(param);
	if (keycode == AKEY)
		p->current_fractal = JULIA_MOUSE;
	if (keycode == SKEY)
		p->current_fractal = JULIA;
	if (keycode == EKEY)
		change_color(param);
	if (keycode == ZKEY)
		change_pres(param, SENS_PRES);
	if (keycode == XKEY)
		change_pres(param, -SENS_PRES);
	if (keycode == ESC)
		free_and_exit(param);
	keyboard_extra(keycode, param);
	calc_and_refresh(param);
	return (0);
}

int		mouse_move_f(int x, int y, void *param)
{
	t_param		*p;

	p = (t_param*)param;
	if (p->current_fractal == JULIA_MOUSE ||
			p->current_fractal == MULTI_JULIA)
	{
		create_j(param, 1, x, y);
		calc_and_refresh(param);
	}
	return (0);
}

int		mouse_fj(int buttom, int x, int y, void *param)
{
	static int	i = 0;

	if (buttom == 5 && i > MIN_ZOOM)
	{
		i--;
		print_j(param, SENS_ZOOM_OUT, x, y);
	}
	if (buttom == 4 && i < MAX_ZOOM)
	{
		i++;
		print_j(param, SENS_ZOOM_IN, x, y);
	}
	calc_and_refresh(param);
	return (0);
}
