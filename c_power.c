/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_power.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 05:07:26 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/23 05:09:34 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		c_power(long double *x_o, long double *y_o, int power)
{
	long double	x;
	long double	y;
	long double	xx;
	long double	yy;
	int			j;

	x = *x_o;
	y = *y_o;
	j = 1;
	while (j < power)
	{
		xx = x * *x_o;
		yy = y * *y_o;
		y = x * *y_o + *x_o * y;
		x = xx - yy;
		j++;
	}
	*x_o = x;
	*y_o = y;
}
