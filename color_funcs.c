/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:05:30 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/11 19:55:57 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		get_spec(t_spec *s, unsigned int color)
{
	s->r = (color & 0xff0000) >> 16;
	s->g = (color & 0x00ff00) >> 8;
	s->b = (color & 0x0000ff);
}

void		get_color_inc(int n_pixels,
		unsigned int color1, unsigned int color2, t_spec *inc)
{
	t_spec	s1;
	t_spec	s2;

	s1.r = (color1 & 0xff0000) >> 16;
	s1.g = (color1 & 0x00ff00) >> 8;
	s1.b = (color1 & 0x0000ff);
	s2.r = (color2 & 0xff0000) >> 16;
	s2.g = (color2 & 0x00ff00) >> 8;
	s2.b = (color2 & 0x0000ff);
	inc->r = ((s2.r - s1.r) / n_pixels);
	inc->g = ((s2.g - s1.g) / n_pixels);
	inc->b = ((s2.b - s1.b) / n_pixels);
}

void		inc_st_color(t_spec *c, t_spec *inc)
{
	c->r += inc->r;
	c->g += inc->g;
	c->b += inc->b;
}
