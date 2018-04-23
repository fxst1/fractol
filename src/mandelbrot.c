/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 01:11:35 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/23 13:34:56 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		mandelbrot2(t_fractol *f, t_fractol_thread *thread)
{
	int			i;
	double		c[2];
	double		z[2];
	double		tmp;

	i = 0;
	c[0] = (thread->x / f->zoom) + f->x1;
	c[1] = (thread->y / f->zoom) + f->y1;
	z[0] = 0;
	z[1] = 0;
	while ((z[0] * z[0]) + (z[1] * z[1]) < 4 && i < f->max_iteration)
	{
		tmp = z[0];
		z[0] = (z[0] * z[0]) - (z[1] * z[1]) + c[0];
		z[1] = (2 * z[1] * tmp) + c[1];
		i++;
	}
	if (i != f->max_iteration)
		(f->draw_point)(f, thread, i);
	else
		put_pixel(f->img, thread->x, thread->y, 0x0);
}

void		*mandelbrot(void *ptr)
{
	t_fractol_thread	*thread;

	thread = (t_fractol_thread*)ptr;
	printf("%lf - %lf\n", (FRACTAL_WIDTH - 1) / thread->data->zoom + thread->data->x1, (FRACTAL_HEIGHT - 1) / thread->data->zoom + thread->data->y1);
	while (thread->x < thread->x_max)
	{
		thread->y = 0;
		while (thread->y < thread->y_max)
		{
			mandelbrot2(thread->data, thread);
			thread->y++;
		}
		thread->x++;
	}
	thread->data->ended_threads++;
	return (NULL);
}

/*
static void		mandelbrot2(t_fractol *f, t_fractol_thread *thread)
{
	int			i;
	double		c[2];
	double		z[2];
	double		tmp;

	i = 0;
	c[0] = (thread->x / f->zoom) + f->x1;
	c[1] = (thread->y / f->zoom) + f->y1;
	z[0] = 0;
	z[1] = 0;
	while ((z[0] * z[0]) + (z[1] * z[1]) < 4 && i < f->max_iteration)
	{
		tmp = z[0];
		z[0] = (z[0] * z[0]) - (z[1] * z[1]) + c[0];
		z[1] = (2 * z[1] * tmp) + c[1];
		i++;
	}
	if (i != f->max_iteration)
		(f->draw_point)(f, thread, i);
	else
		put_pixel(f->img, thread->x, thread->y, 0x0);
}

void		*mandelbrot(void *ptr)
{
	t_fractol_thread	*thread;

	thread = (t_fractol_thread*)ptr;
	printf("%lf - %lf\n", (FRACTAL_WIDTH - 1) / thread->data->zoom + thread->data->x1, (FRACTAL_HEIGHT - 1) / thread->data->zoom + thread->data->y1);
	while (thread->x < thread->x_max)
	{
		thread->y = 0;
		while (thread->y < thread->y_max)
		{
			mandelbrot2(thread->data, thread);
			thread->y++;
		}
		thread->x++;
	}
	thread->data->ended_threads++;
	return (NULL);
}
*/
void		mandelbrot_reset(t_fractol *f)
{
	f->x1 = -4.75;
	f->x2 = -0.25;
	f->y1 = -2.2;
	f->y2 = 0.2;
	f->zoom = 200;
	f->fractal_name = "mandelbrot";
	f->draw_fractal = &mandelbrot;
	f->reset_fractal = &mandelbrot_reset;
}
