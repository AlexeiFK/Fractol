

#ifndef FDF_H
# define FDF_H

#include "config.h"
#include "keys.h"
#include <bsd/string.h>


typedef struct			s_spec
{
	float			r;
	float			g;
	float			b;
}				t_spec;

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
	int		color_scheme;
	int		pres;
	long double	julia_x;
	long double	julia_y;
	long double	j_start_x;
	long double	j_start_y;
	long double	j_mult;
	int		current_fractal;
	t_spec		**palette;
	int		pal_size;
	int		n;
	void		 *(*fractal_func)(void*);
}			t_param;

typedef struct		s_thread_param
{
	int		pixel_start;
	t_param		*p;
}			t_thread_param;

int		mouse_f(int buttom, int x, int y, void *param);
int		keyboard_f(int keycode, void *param);
int		mouse_fj(int buttom, int x, int y, void *param);
int		keyboard_fj(int keycode, void *param);
int		hook_f(void *param);
int		mouse_move_f(int x, int y, void *param);
void		change_color(t_param *param);
void		change_color_j(t_param *param);
void		shift_set(t_param *param, long double x, long double y);
void		change_pres(t_param *param, int pres);
void		set_color(t_param *param, int i, int i_max, t_spec *spec);
void		change_color_par(t_param *param, int k1, int k2, int k3);
void		print(t_param *param, long double mult, long double x, long double y);
void		print_j(t_param *param, long double mult, long double x, long double y);
void		create_j(t_param *param, long double mult, long double x, long double y);
void		x_y_convert(t_param *param, long double x, long double y); //long double *new_x, long double *new_y)
void		ch_pixel_put(t_param *param, int x, int y, t_spec *c);
void		choose_color(t_spec *to_color, int color_scheme, int size, int i);
void		choose_colors(int *colors, int *n_colors, int scheme_number);
t_spec		**new_palette(int size, int color_scheme);
void		free_palette(t_spec **pal, int size);
void		random_color(t_param *param);
void		random_color_j(t_param *param);
void		change_pres_j(t_param *param, int pres);
void		change_n(t_param *param, int n);
void		*trd_func(void *p);
void		*trd_funcj(void *p);
void		*trd_func_ship(void *p);
void		*trd_func_tricorn(void *p);
void		*trd_func_smooth(void *p);
void		*trd_func_multibrot(void *p);
void		*trd_func_multijulia(void *p);
void		calc_and_refresh(t_param *param);
void		c_power(long double *x_o, long double *y_o, int power);

#endif
