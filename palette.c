


#include <pthread.h>
#include "fractol.h"
#include "mlx.h"
#include "config.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


void		get_spec(t_spec *s, unsigned int color)
{
	s->r = (color & 0xff0000) >> 16;
	s->g = (color & 0x00ff00) >> 8;
	s->b = (color & 0x0000ff);
}
void		get_color_inc(int n_pixels, unsigned int color1, unsigned int color2, t_spec *inc)
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

void		choose_inner_color(t_spec *to_color, int color_scheme, int size, int i)
{
	if ((color_scheme % 2 == 1) && (size == i))
	{
		to_color->r = 0;
		to_color->g = 0;
		to_color->b = 0;
	}
	if ((color_scheme % 2 == 0) && (size == i))
	{
		to_color->r = 255;
		to_color->g = 255;
		to_color->b = 255;
	}
}

void		fill_up(t_spec **pal, int start, int size_to_fill, int *colors)
{
	int		i;
	int		end;
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
	int		i;
	int		n_colors;
	int		colors[MAX_COLORS];

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
	new[size]->r = 0;
	new[size]->g = 0;
	new[size]->b = 0;
	return (new);
}

void		free_palette(t_spec **pal, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		free(pal[i]);
		i++;
	}
	free(pal);
}

/*
void		choose_wave_color(t_spec *to_color, int color_scheme, int size, int i)
{
	float	color_inc;

	color_inc = (255.0 * 30) / (size + 1);
	if ((color_scheme == 8) || (color_scheme == 9))
	{
		to_color->r = ((int)round(i * color_inc)) % 256;
		to_color->g = ((int)round(i * color_inc)) % 256;
		to_color->b = ((int)round(i * color_inc)) % 256;
	}
	if ((color_scheme == 10) || (color_scheme == 11))
		to_color->r = ((int)round(i * color_inc)) % 256;
	if ((color_scheme == 12) || (color_scheme == 13))
		to_color->g = ((int)round(i * color_inc)) % 256;
	if ((color_scheme == 14) || (color_scheme == 15))
		to_color->b = ((int)round(i * color_inc)) % 256;
	if ((color_scheme == 15) || (color_scheme == 16))
	{
		to_color->r = ((int)round(i * 0.1 * color_inc)) % 256;
		to_color->g = ((int)round(i * 0.8 * color_inc)) % 256;
		to_color->b = ((int)round(i * 0.3 * color_inc)) % 256;
	}
	if ((color_scheme == 17) || (color_scheme == 18))
	{
		to_color->r = ((int)round(i * 0.7 * color_inc)) % 256;
		to_color->g = ((int)round(i * 0.1 * color_inc)) % 256;
		to_color->b = ((int)round(i * 0.4 * color_inc)) % 256;
	}
}

void		choose_color(t_spec *to_color, int color_scheme, int size, int i)
{
	float	color_inc;

	color_inc = 255.0 / (size + 1);
	to_color->r = 0;
	to_color->g = 0;
	to_color->b = 0;
	if ((color_scheme == 0) || (color_scheme == 1))
	{
		to_color->r = round(i * color_inc);
		to_color->g = round(i * color_inc);
		to_color->b = round(i * color_inc);
	}
	else if ((color_scheme == 2) || (color_scheme == 3))
		to_color->r = round(i * color_inc);
	else if ((color_scheme == 4) || (color_scheme == 5))
		to_color->g = round(i * color_inc);
	else if ((color_scheme == 6) || (color_scheme == 7))
		to_color->b = round(i * color_inc);
	else
		choose_wave_color(to_color, color_scheme, size, i);
}



void		choose_random_color(t_spec *to_color, int color_scheme, int size, int i)
{
	srand(i * time(NULL));
	to_color->r = rand() % 256;
	to_color->g = rand() % 256;
	to_color->b = rand() % 256;
}
		
		if (color_scheme == RANDOM_SCHEME)
		{
			choose_random_color(new[i], color_scheme, size, i);
		}
		else
		{
			choose_color(new[i], color_scheme, size, i);
			choose_inner_color(new[i], color_scheme, size, i);
		}
		
*/
