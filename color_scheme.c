/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_scheme.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:32:17 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/12 21:07:47 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include <stdlib.h>
#include <time.h>
#include "colors.h"

void		choose_random_color(int *colors, int *n_colors)
{
	int		i;

	i = 0;
	srand(time(NULL));
	*n_colors = rand() % (MAX_COLORS - 2) + 2;
	while (i < *n_colors)
	{
		colors[i] = (rand() % 256) * (rand() % 256) * (rand() % 256);
		i++;
	}
}

void		choose_colors_extra3(int *colors, int *n_colors, int color_scheme)
{
	if (color_scheme == 9)
	{
		colors[0] = BLACK;
		colors[1] = 0x11ffff;
		*n_colors = 2;
	}
	else if (color_scheme == 10)
	{
		colors[0] = RED;
		colors[1] = 0x00ffff;
		colors[2] = GREEN;
		colors[3] = 0xff00ff;
		colors[4] = BLUE;
		colors[5] = 0xffff00;
		*n_colors = 6;
	}
	else if (color_scheme == 11)
	{
		colors[0] = BLACK;
		colors[1] = 0xffb273;
		*n_colors = 2;
	}
}

void		choose_colors_extra2(int *colors, int *n_colors, int color_scheme)
{
	if (color_scheme == 6)
	{
		colors[0] = 0xbcaa73;
		colors[1] = WHITE;
		colors[2] = BLACK;
		*n_colors = 3;
	}
	else if (color_scheme == 7)
	{
		colors[0] = BLACK;
		colors[1] = WHITE;
		colors[2] = BLACK;
		colors[3] = WHITE;
		colors[4] = BLACK;
		*n_colors = 5;
	}
	else if (color_scheme == 8)
	{
		colors[0] = BLUE;
		colors[1] = GREEN;
		colors[2] = RED;
		*n_colors = 3;
	}
	else
		choose_colors_extra3(colors, n_colors, color_scheme);
}

void		choose_colors_extra1(int *colors, int *n_colors, int color_scheme)
{
	if (color_scheme == 3)
	{
		colors[0] = 0x00aaff;
		colors[1] = 0xffffaa;
		colors[2] = 0x000a00;
		*n_colors = 3;
	}
	else if (color_scheme == 4)
	{
		colors[0] = 0x845ec2;
		colors[1] = 0xd65db1;
		colors[2] = 0xffc75f;
		*n_colors = 3;
	}
	else if (color_scheme == 5)
	{
		colors[0] = BLACK;
		colors[1] = GREEN;
		colors[2] = RED;
		*n_colors = 3;
	}
	else if (color_scheme == RANDOM_SCHEME)
		choose_random_color(colors, n_colors);
	else
		choose_colors_extra2(colors, n_colors, color_scheme);
}

void		choose_colors(int *colors, int *n_colors, int color_scheme)
{
	if (color_scheme == 0)
	{
		colors[0] = WHITE;
		colors[1] = WHITE;
		*n_colors = 2;
	}
	else if (color_scheme == 1)
	{
		colors[0] = RED;
		colors[1] = 0xffff00;
		colors[2] = GREEN;
		colors[3] = 0x00ffff;
		colors[4] = BLUE;
		colors[5] = 0xff00ff;
		*n_colors = 6;
	}
	else if (color_scheme == 2)
	{
		colors[0] = BLUE;
		colors[1] = 0xffff00;
		*n_colors = 2;
	}
	else
		choose_colors_extra1(colors, n_colors, color_scheme);
}
