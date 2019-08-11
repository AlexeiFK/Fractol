/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:02:36 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/11 19:09:27 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "fractol.h"
#include "mlx.h"
#include "config.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void		fill_up(t_spec **pal, int start, int size_to_fill, int *colors)
{
	int			i;
	int			end;
	t_spec		inc;
	t_spec		tmp;

	i = start;
	end = start + size_to_fill;
	get_color_inc(size_to_fill, colors[0], colors[1], &inc);
	get_spec(&tmp, colors[0]);
	while (i < end)
	{
		inc_st_color(&tmp, &inc);
		pal[i]->r = tmp.r;
		pal[i]->g = tmp.g;
		pal[i]->b = tmp.b;
		i++;
	}
}

void		fill_up_palette(t_spec **pal, int size, int *colors, int n_colors)
{
	int	i;
	int	j;
	int	part_size;

	part_size = size / (n_colors - 1);
	i = 0;
	j = 0;
	while ((i < size) && (j < (n_colors - 1)))
	{
		fill_up(pal, i, part_size, colors + j);
		j++;
		i += part_size;
	}
}

t_spec		**new_palette(int size, int color_scheme)
{
	t_spec		**new;
	int			i;
	int			n_colors;
	int			colors[MAX_COLORS];

	size++;
	if (!(new = (t_spec**)malloc(sizeof(t_spec*) * size)))
		return (NULL);
	i = 0;
	while (i <= size)
	{
		if (!(new[i] = (t_spec*)malloc(sizeof(t_spec))))
			return (NULL);
		i++;
	}
	choose_colors(colors, &n_colors, color_scheme);
	fill_up_palette(new, size, colors, n_colors);
	new[size - 1]->r = 0;
	new[size - 1]->g = 0;
	new[size - 1]->b = 0;
	return (new);
}

void		free_palette(t_spec **pal, int size)
{
	int	i;

	size++;
	i = 0;
	while (i <= size)
	{
		free(pal[i]);
		i++;
	}
	free(pal);
}
