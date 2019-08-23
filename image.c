/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 05:09:10 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/23 05:10:28 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include "config.h"
#include "libft.h"
#include <stdlib.h>

void		ch_pixel_put(t_param *param, int x, int y, t_spec *c)
{
	unsigned char	*s;

	s = param->s;
	s += (param->size * y);
	s[x * 4] = c->b;
	s[x * 4 + 1] = c->g;
	s[x * 4 + 2] = c->r;
}

void		put_info(t_param *param)
{
	char	*pres_info;

	pres_info = ft_itoa(param->pres);
	if (param->color_scheme == 0)
		mlx_string_put(param->mlx_ptr, param->win_ptr,
			BUFFER, BUFFER, 0x808080, pres_info);
	else
		mlx_string_put(param->mlx_ptr, param->win_ptr,
			BUFFER, BUFFER, 0xffffff, pres_info);
	free(pres_info);
}

void		calc_and_refresh(t_param *param)
{
	trd_starter(param, param->fractal_func);
	if (param->current_fractal == MAND_CHESS)
		chess_scale(param);
	mlx_put_image_to_window(param->mlx_ptr,
			param->win_ptr, param->img_ptr, 0, 0);
	put_info(param);
}
