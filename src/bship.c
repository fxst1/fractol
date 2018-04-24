/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bship.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 01:11:35 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/24 09:16:35 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	bship2(t_fractol_thread *thread, double i, double j, t_complex c)
{
	int			iter;
	t_complex	z;
	double		tmp;

	iter = 0;
	z.r = 0;
	z.i = 0;
	tmp = 0;
	while (z.r * z.r + z.i * z.i < 4 && iter < thread->ondraw->max_iter)
	{
		tmp = z.r * z.r - z.i * z.i + c.r;
		z.i = 2 * fabs(z.r * z.i) + c.i;
		z.r = tmp;
		iter++;
	}
//	printf("%lf - %lf\n", c.r, c.i);
	(*thread->ondraw->draw_point)(thread->ondraw, j, i, iter);
}

void		*bship(void *ptr)
{
	int					i;
	int					j;
	t_fractol_thread	*thread;
	t_complex			c;

	thread = (t_fractol_thread*)ptr;
	i = thread->y;
	while (i < thread->y_max)
	{
		j = thread->x;
		c.i = (i - FRACTAL_HEIGHT / 2) * (thread->ondraw->fractal.bship.scale)
			+ thread->ondraw->fractal.bship.cy;
		while (j < thread->x_max)
		{
			c.r = (j - FRACTAL_WIDTH / 2) * (thread->ondraw->fractal.bship.scale)
				+ thread->ondraw->fractal.bship.cx;
			bship2(thread, i, j, c);
			j++;
		}
		i++;
	}
	pthread_mutex_lock(&thread->ondraw->mutex);
	thread->ondraw->running_threads--;
	pthread_mutex_unlock(&thread->ondraw->mutex);
	return (NULL);
}

void		bship_reset(t_fractal *f)
{
	f->name = "Burning Ship";
	f->max_iter = 50;
	f->depth = 1;
	f->type = BSHIP;
	f->fractal.bship.cx = -0.431250;
	f->fractal.bship.cy = 1.115625;
	f->fractal.bship.scale = 0.003125;
	f->draw_fractal = &bship;
	f->reset_fractal = &bship_reset;
}
