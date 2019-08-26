/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:58:16 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/26 09:20:25 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H
/*
** WINDOW CONFIG **
*/
# define W_NAME "Fractol42"
# define WINDOW_HEIGTH 900
# define WINDOW_WIDTH 1100
# define WINDOW_H_C WINDOW_HEIGTH/2
# define WINDOW_W_C WINDOW_WIDTH/2
/*
 ** SCREEN_UNITS is a factor to convert real coordinates to pixels on screen
*/
# define SCREEN_UNITS -4
/*
 ** BUFFER is a "frame" of empty pixels around fractal
*/
# define BUFFER 50

# define FRACTAL_NAME_LIMIT 10
# define N_FRACTAL_LIMIT 10

# define COLOR_SCHEME_MAX 12
# define RANDOM_SCHEME 2048
# define MAX_COLORS 10

/*
 ** Special paramets to use smooth coloring
*/
# define SMOOTH_ESCAPE 65536
# define SMOOTH_EXTRA_PAL 25

/*
 ** fractals ids
*/
# define JULIA 1
# define JULIA_MOUSE 8
# define MULTI_JULIA 9
# define MAND 0
# define MAND_SMOOTH 4
# define MAND_CHESS 7

# define MULTI_POWER_MAX 10
# define MULTI_POWER_MIN 2

# define THREADS_NUM 4

# define SENS_J 0.004
# define SENS_HOR 20
# define SENS_VERT 20
# define SENS_PRES 20
# define SENS_ZOOM_IN 1.1
# define SENS_ZOOM_OUT 1/1.1
# define MAX_ZOOM 430
# define MIN_ZOOM -10

#endif
