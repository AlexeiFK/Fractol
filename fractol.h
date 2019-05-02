

#ifndef FDF_H
# define FDF_H

#include "config.h"
#include <bsd/string.h>

typedef struct		s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	void		*menu_ptr;
	unsigned char	*s;
	int		size;
	long double	start_x;
	long double	start_y;
	long double	mult;
	int		k;
	int		k1;
	int		k2;
	int		k3;
	int		pres;
}			t_param;

typedef struct			s_spec
{
	float			r;
	float			g;
	float			b;
}				t_spec;

int		mouse_f(int buttom, int x, int y, void *param);
int		keyboard_f(int keycode, void *param);
int		hook_f(void *param);
void		change_color(t_param *param);
void		change_pres(t_param *param, int pres);
void		change_color_par(t_param *param, int k1, int k2, int k3);
void		print(t_param *param, long double mult, int x, int y);
void		x_y_convert(t_param *param, long double x, long double y); //long double *new_x, long double *new_y)
void		ch_pixel_put(t_param *param, int x, int y, t_spec *c);


#endif
