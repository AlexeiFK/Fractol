


#include <pthread.h>
#include "fractol.h"
#include "mlx.h"
#include "config.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


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

t_spec		**new_palette(int size, int color_scheme)
{
	t_spec		**new;
	int		i;

	if (!(new = (t_spec**)malloc(sizeof(t_spec*) * size)))
		return (NULL);
	i = 0;
	while (i <= size)
	{
		if (!(new[i] = (t_spec*)malloc(sizeof(t_spec))))
			return (NULL);
		if (color_scheme == RANDOM_SCHEME)
		{
			choose_random_color(new[i], color_scheme, size, i);
		}
		else
		{
			choose_color(new[i], color_scheme, size, i);
			choose_inner_color(new[i], color_scheme, size, i);
		}
		i++;
	}
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
