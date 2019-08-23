/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trd_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeor-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 05:07:59 by rjeor-mo          #+#    #+#             */
/*   Updated: 2019/08/23 05:08:50 by rjeor-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "fractol.h"
#include "config.h"
#include <stdlib.h>

void		trd_starter(t_param *param, void *(*func)(void*))
{
	pthread_t		t[THREADS_NUM];
	t_thread_param	p[THREADS_NUM];
	int				i;

	i = 0;
	while (i < THREADS_NUM)
	{
		p[i].pixel_start = i;
		p[i].p = param;
		pthread_create(&t[i], NULL, func, &p[i]);
		i++;
	}
	i = 0;
	while (i < THREADS_NUM)
	{
		pthread_join(t[i], NULL);
		i++;
	}
}
