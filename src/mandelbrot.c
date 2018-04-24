/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 01:11:35 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/24 11:33:33 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	mandelbrot2(t_fractol_thread *thread, double i, double j, t_complex c)
{
	int		iter;
	double	zx;
	double	zy;
	double	zx2;
	double	zy2;

	iter = 0;
	zx =  0;
	zy = 0;
	zx2 = 0;
	zy2 = 0;
	while (zx2 + zy2 < 4 && iter < thread->ondraw->max_iter)
	{
		zy = 2 * zx * zy + c.i;
		zx = zx2 - zy2 + c.r;
		zx2 = zx * zx;
		zy2 = zy * zy;
		iter++;
	}
	(*thread->ondraw->draw_point)(thread->ondraw, j, i, iter);
}

void		*mandelbrot(void *ptr)
{
	int					i;
	int					j;
	t_complex			c;
	t_fractol_thread	*thread;

	thread = (t_fractol_thread*)ptr;
	i = thread->y;
	while (i < thread->y_max)
	{
		j = thread->x;
		c.i = (i - FRACTAL_HEIGHT / 2) * thread->ondraw->fractal.mandelbrot.scale
			+ thread->ondraw->fractal.mandelbrot.cy;
		while (j < thread->x_max)
		{
			c.r = (j - FRACTAL_WIDTH / 2) * thread->ondraw->fractal.mandelbrot.scale
				+ thread->ondraw->fractal.mandelbrot.cx;
			mandelbrot2(thread, i, j, c);
			j++;
		}
		i++;
	}
	return (NULL);
}

void		mandelbrot_reset(t_fractal *f)
{
	f->name = "mandelbrot";
	f->max_iter = 300;
	f->depth = 1;
	f->type = MANDELBROT;
	f->fractal.mandelbrot.cx = -0.5;
	f->fractal.mandelbrot.cy = 2.0;
	f->fractal.mandelbrot.scale = 1.0 / 256;
	f->draw_fractal = &mandelbrot;
	f->reset_fractal = &mandelbrot_reset;
}
