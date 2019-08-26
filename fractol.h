/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:03:43 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/26 13:02:38 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

typedef struct		s_spec
{
	float			r;
	float			g;
	float			b;
}					t_spec;

typedef struct		s_param
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	void			*menu_ptr;

	unsigned char	*s;
	int				size;

	long double		start_x;
	long double		start_y;
	long double		mult;
	int				pres;
	int				n;

	long double		julia_x;
	long double		julia_y;
	long double		j_start_x;
	long double		j_start_y;
	long double		j_mult;

	int				color_scheme;
	t_spec			**palette;

	int				current_fractal;
	char			is_chess;
	void			*(*fractal_func)(void*);
}					t_param;

typedef struct		s_thread_param
{
	int				pixel_start;
	t_param			*p;
}					t_thread_param;

int					mouse_f(int buttom, int x, int y, void *param);
int					keyboard_f(int keycode, void *param);
int					mouse_fj(int buttom, int x, int y, void *param);
int					keyboard_fj(int keycode, void *param);
int					hook_f(void *param);
int					mouse_move_f(int x, int y, void *param);

void				usage_msg(void);
void				free_and_exit(t_param *param);

void				mlx_setup(t_param *param, int fractal);
void				get_funcs(void *(**f_funcs)(void*));
void				set_controls(int fractal_num, t_param *param);
int					get_fractal_number(char *name);

void				change_color(t_param *param);
void				change_color_j(t_param *param);
void				shift_set(t_param *param, long double x, long double y);
void				shift_setj(t_param *param, long double x, long double y);
void				shift_julia_param(t_param *param,
					long double x, long double y);
void				change_pres(t_param *param, int pres);
void				zoom_mand(t_param *param,
					long double mult, long double x, long double y);
void				print_j(t_param *param,
					long double mult, long double x, long double y);
void				create_j(t_param *param,
					long double mult, long double x, long double y);
void				change_pres_j(t_param *param, int pres);
void				change_n(t_param *param, int n);
void				choose_color(t_spec *to_color,
					int color_scheme, int size, int i);
void				choose_colors(int *colors,
					int *n_colors, int scheme_number);
t_spec				**new_palette(int size, int color_scheme);
void				free_palette(t_spec **pal, int size);
void				random_color(t_param *param);
void				random_color_j(t_param *param);

void				trd_starter(t_param *param, void *(*func)(void*));
void				*trd_func_mand(void *p);
void				*trd_func_julia(void *p);
void				*trd_func_ship(void *p);
void				*trd_func_tricorn(void *p);
void				*trd_func_smooth(void *p);
void				*trd_func_multibrot(void *p);
void				*trd_func_multijulia(void *p);
void				*trd_func_cmand(void *p);
void				*trd_func_cship(void *p);
void				*trd_func_cjulia(void *p);
void				*trd_func_cship(void *p);
void				*trd_func_ctricorn(void *p);
void				*trd_func_cmultibrot(void *p);
void				*trd_func_cmultijulia(void *p);
void				calc_and_refresh(t_param *param);

void				chess_scale(t_param *param);
void				c_power(long double *x_o, long double *y_o, int power);
void				ch_pixel_put(t_param *param, int x, int y, t_spec *c);

void				get_spec(t_spec *s, unsigned int color);
unsigned int		get_hex(t_spec *s);
void				get_color_inc(int n_pixels,
					unsigned int color1, unsigned int color2, t_spec *inc);
void				inc_st_color(t_spec *c, t_spec *inc);

void				ft_reader(t_param *param);

#endif
