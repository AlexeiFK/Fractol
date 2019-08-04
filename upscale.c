
#include <pthread.h>
#include "fractol.h"
#include "mlx.h"
#include "config.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>

void	biliner_put_4dots(t_param *param, int x, int y)
{
	unsigned char	*sm;
	unsigned char	*sp;
	unsigned char	*sn;
	int		temp;

	sp = param->s;
	sp += (param->size * (y - 1));
	sn = param->s;
	sn += (param->size * (y + 1));
	sm = param->s;
	sm += (param->size * y);
	temp = (sp[x * 4] + sn[x * 4] + sm[(x + 1) * 4] + sm[(x - 1) * 4]) / 4;
	sm[x * 4] = temp;
	temp = (sp[x * 4 + 1] + sn[x * 4 + 1] + sm[(x + 1) * 4 + 1] + sm[(x - 1) * 4 + 1]) / 4;
	sm[x * 4 + 1] = temp;
	temp = (sp[x * 4 + 2] + sn[x * 4 + 2] + sm[(x + 1) * 4 + 2] + sm[(x - 1) * 4 + 2]) / 4;
	sm[x * 4 + 2] = temp;
}

void	biliner_put(t_param *param, int x, int y)
{
	unsigned char	*sm;
	unsigned char	*sp;
	unsigned char	*sn;
	int		temp;

	sp = param->s;
	sp += (param->size * (y - 1));
	sn = param->s;
	sn += (param->size * (y + 1));
	sm = param->s;
	sm += (param->size * y);
	temp = (sp[x * 4] + sn[x * 4]) / 2;
	sm[x * 4] = temp;
	temp = (sp[x * 4 + 1] + sn[x * 4 + 1]) / 2;
	sm[x * 4 + 1] = temp;
	temp = (sp[x * 4 + 2] + sn[x * 4 + 2]) / 2;
	sm[x * 4 + 2] = temp;
}

void	biliner_put_hor(t_param *param, int x, int y)
{
	unsigned char	*sm;
	int		temp;

	sm = param->s;
	sm += (param->size * y);
	temp = (sm[(x + 1) * 4] + sm[(x - 1) * 4]) / 2;
	sm[x * 4] = temp;
	temp = (sm[(x + 1) * 4 + 1] + sm[(x - 1) * 4 + 1]) / 2;
	sm[x * 4 + 1] = temp;
	temp = (sm[(x + 1) * 4 + 2] + sm[(x - 1) * 4 + 2]) / 2;
	sm[x * 4 + 2] = temp;
}

void	chess_scale(t_param *param)
{
	int	x;
	int	y;
	int	y_start;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		if (x % 2 == 0)
			y = 1;
		else
			y = 0;
		while (y < WINDOW_HEIGTH)
		{
			biliner_put_4dots(param, x, y);
			y += 2;
		}
		x += 1;
	}
}
void	upscale(t_param *param)
{
	int	x;
	int	y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 1;
		while (y < WINDOW_HEIGTH)
		{
			biliner_put(param, x, y);
			y += 2;
		}
		x += 2;
	}
	x = 1;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGTH)
		{
			biliner_put_hor(param, x, y);
			y += 2;
		}
		x += 2;
	}
	x = 1;
	while (x < WINDOW_WIDTH)
	{
		y = 1;
		while (y < WINDOW_HEIGTH)
		{
			biliner_put(param, x, y);
			y += 2;
		}
		x += 2;
	}
}
