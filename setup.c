/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:55:03 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/11 18:59:38 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "fractol.h"
#include "mlx.h"

static int	min_mult(int width, int height)
{
	if (width > height)
		return (height / SCREEN_UNITS);
	else
		return (width / SCREEN_UNITS);
}

void		mlx_setup(t_param *param, int fractal)
{
	int	bits;
	int	endian;

	param->mlx_ptr = mlx_init();
	param->win_ptr =
		mlx_new_window(param->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGTH, W_NAME);
	param->img_ptr = mlx_new_image(param->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGTH);
	param->start_x = WINDOW_W_C;
	param->start_y = WINDOW_H_C;
	param->j_start_x = WINDOW_W_C;
	param->j_start_y = WINDOW_H_C;
	param->current_fractal = fractal;
	param->pres = 100;
	param->n = 2;
	param->color_scheme = 0;
	if (fractal == MAND_SMOOTH)
		param->palette =
			new_palette(param->pres * SMOOTH_EXTRA_PAL, param->color_scheme);
	else
		param->palette = new_palette(param->pres, param->color_scheme);
	param->mult = min_mult(WINDOW_WIDTH - BUFFER, WINDOW_HEIGTH - BUFFER);
	param->j_mult = min_mult(WINDOW_WIDTH - BUFFER, WINDOW_HEIGTH - BUFFER);
	param->s = (unsigned char*)
		mlx_get_data_addr(param->img_ptr, &bits, &(param->size), &endian);
}

int			get_fractal_number(char *s)
{
	char	fractals[FRACTAL_NAME_LIMIT][N_FRACTAL_LIMIT];
	int		i;

	ft_strcpy(fractals[0], "Mand");
	ft_strcpy(fractals[1], "Bsf");
	ft_strcpy(fractals[2], "Tricorn");
	ft_strcpy(fractals[3], "MultiB");
	ft_strcpy(fractals[4], "MandSm");
	ft_strcpy(fractals[5], "BsfC");
	ft_strcpy(fractals[6], "TricornC");
	ft_strcpy(fractals[7], "MandC");
	ft_strcpy(fractals[8], "Julia");
	ft_strcpy(fractals[9], "MultiJ");
	i = 0;
	while (i < N_FRACTAL_LIMIT)
	{
		if (ft_strcmp(s, fractals[i]) == 0)
			return (i);
		++i;
	}
	return (-1);
}

void		get_funcs(void *(**f_funcs)(void*))
{
	f_funcs[0] = trd_func_mand;
	f_funcs[1] = trd_func_ship;
	f_funcs[2] = trd_func_tricorn;
	f_funcs[3] = trd_func_multibrot;
	f_funcs[4] = trd_func_smooth;
	f_funcs[5] = trd_func_ship;
	f_funcs[6] = trd_func_tricorn;
	f_funcs[7] = trd_func_cmand;
	f_funcs[8] = trd_func_julia;
	f_funcs[9] = trd_func_multijulia;
}

void		set_controls(int fractal_num, t_param *param)
{
	if (fractal_num < 8)
	{
		mlx_key_hook(param->win_ptr, keyboard_f, (void*)(param));
		mlx_mouse_hook(param->win_ptr, mouse_f, (void*)(param));
	}
	else if (fractal_num >= 8)
	{
		mlx_key_hook(param->win_ptr, keyboard_fj, (void*)(param));
		mlx_mouse_hook(param->win_ptr, mouse_fj, (void*)(param));
		mlx_hook(param->win_ptr, 6, (1L << 6), mouse_move_f, (void*)(param));
	}
}
