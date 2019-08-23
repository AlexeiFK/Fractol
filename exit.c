/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:25:43 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/23 04:18:05 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "mlx.h"
#include "fractol.h"

static void	controls_msg(void)
{
	ft_putstr("Arrows - Shift\n");
	ft_putstr("Mouse wheel - zoom\n");
	ft_putstr("Z - increase precision\n");
	ft_putstr("X - dicrease precision\n");
	ft_putstr("E - change color\n");
	ft_putstr("R - random color\n");
	ft_putstr("Q - increase power in multifractals\n");
	ft_putstr("W - dicrease power in multifractals\n");
	ft_putstr("A - turn on mouse julia changing\n");
	ft_putstr("S - turn off mouse julia changing\n");
	ft_putstr("TFGH - change julia param\n");
	ft_putstr("Esc - exit\n");
}
void		usage_msg(void)
{
	ft_putstr("usage: ./fractol [fractal_name]\n");
	ft_putstr("fractal names:\n");
	ft_putstr("Mand = Mandelbrot set\n");
	ft_putstr("Julia = Julia set\n");
	ft_putstr("Bsf = Burning Ship Fractal\n");
	ft_putstr("Tricorn = Tricorn set\n");
	ft_putstr("MultiB = Multibrot sets\n");
	ft_putstr("MandSm = Mandelbrot set smooth color\n");
	ft_putstr("MultiJ = MultiJulia sets\n");
	ft_putstr("-----------------------------\n");
	controls_msg();
	exit(0);
}

void		free_and_exit(t_param *param)
{
	free_palette(param->palette, param->pres);
	mlx_destroy_window(param->mlx_ptr, param->win_ptr);
	mlx_destroy_image(param->mlx_ptr, param->img_ptr);
	exit(0);
}
