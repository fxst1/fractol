/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 01:11:35 by fxst1             #+#    #+#             */
/*   Updated: 2018/06/12 18:57:35 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	julia2(t_fractol_thread *thread, double i, double j, t_complex z)
{
	int			iter;
	double		tmp;
	t_complex	tmp2;

	iter = 0;
	tmp = z.r;
	tmp2 = thread->ondraw->fractal.julia.cst;
	while (z.r * z.r + z.i * z.i < 4 && iter < thread->ondraw->max_iter)
	{
		tmp = z.r;
		z.r = z.r * z.r - z.i * z.i + tmp2.r;
		z.i = 2 * tmp * z.i + tmp2.i;
		iter++;
	}
	(*thread->ondraw->draw_point)(thread->ondraw, j, i, iter);
}

void		*julia(void *ptr)
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
		c.i = (i - FRACTAL_HEIGHT / 2) * (thread->ondraw->fractal.julia.scale)
			+ thread->ondraw->fractal.julia.cy;
		while (j < thread->x_max)
		{
			c.r = (j - FRACTAL_WIDTH / 2) *
				(thread->ondraw->fractal.julia.scale)
				+ thread->ondraw->fractal.julia.cx;
			julia2(thread, i, j, c);
			j++;
		}
		i++;
	}
	return (NULL);
}

void		julia_reset(t_fractal *f)
{
	f->name = "Julia";
	f->max_iter = 10;
	f->depth = 1;
	f->type = JULIA;
	f->fractal.julia.cst.r = -0.7;
	f->fractal.julia.cst.i = -0.27015;
	f->fractal.julia.cx = 0;
	f->fractal.julia.cy = 2.0;
	f->fractal.julia.scale = 1.0 / 256;
	f->draw_fractal = &julia;
	f->reset_fractal = &julia_reset;
}
