/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:25:43 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/12 21:11:55 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "mlx.h"
#include "fractol.h"

void	usage_msg(void)
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
	exit(0);
}

void	free_and_exit(t_param *param)
{
	free_palette(param->palette, param->pres);
	mlx_destroy_window(param->mlx_ptr, param->win_ptr);
	mlx_destroy_image(param->mlx_ptr, param->img_ptr);
	exit(0);
}
