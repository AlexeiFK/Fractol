/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_to_fdf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 11:55:53 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/26 13:14:49 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "fractol.h"
#include "config.h"

int		get_pal_i(t_spec **pal, t_spec *c, int size)
{
	int	i;

	size++;
	i = 0;
	while (i <= size)
	{
		if (pal[i]->r == c->r)
			if (pal[i]->g == c->g)
				if (pal[i]->b == c->b)
					return (i);
		i++;
	}
	return (0);
}

int		get_fdf_info(t_param *param, int x, int y, t_spec *c)
{
	unsigned char	*s;
	int				xm;

	xm = x << 2;
	s = param->s;
	s += (param->size * y);
	c->b = s[xm];
	c->g = s[xm + 1];
	c->r = s[xm + 2];
	return (get_pal_i(param->palette, c, param->pres));
}

void	ft_reader(t_param *param)
{
	int		fd;
	int		w;
	int		h;
//	int		info;
	t_spec	c;

	fd = open("fdf.fdf", O_WRONLY);
	if (fd < 0)
		usage_msg();
	w = 0;
	h = 0;
	while (h < WINDOW_HEIGTH)
	{
		w = 0;
		while (w < WINDOW_WIDTH)
		{
			ft_putnbr_fd(get_fdf_info(param, w, h, &c), fd);
			ft_putchar_fd(' ', fd);
			w++;
		}
		ft_putchar_fd('\n', fd);
		h++;
	}
}
