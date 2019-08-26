/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_param_julia.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 09:40:35 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/26 09:41:10 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			create_j(t_param *param,
		long double mult, long double x, long double y)
{
	param->mult = param->mult * mult;
	param->julia_x = ((param->start_x) - x) / param->mult;
	param->julia_y = (y - (param->start_y)) / param->mult;
}

void			print_j(t_param *param,
		long double mult, long double x, long double y)
{
	long double		res1;
	long double		res2;

	res1 = (param->j_start_x - x) * mult;
	res2 = (param->j_start_y - y) * mult;
	param->j_start_x = x + res1;
	param->j_start_y = y + res2;
	param->j_mult = param->j_mult * mult;
}
