/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:24:16 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/26 11:27:43 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>

#include "fractol.h"
#include "mlx.h"
#include "config.h"

int		main(int argc, char **argv)
{
	t_param		param;
	int			fractal_num;
	void		*(*f_funcs[N_FRACTAL_LIMIT])(void*);

	if (argc != 2)
		usage_msg();
	get_funcs(f_funcs);
	fractal_num = get_fractal_number(argv[1]);
	if (fractal_num != -1)
	{
		mlx_setup(&param, fractal_num);
		set_controls(fractal_num, &param);
		param.fractal_func = f_funcs[fractal_num];
		calc_and_refresh(&param);
	}
	else
		usage_msg();
	calc_and_refresh(&param);
	mlx_loop(param.mlx_ptr);
	return (0);
}
