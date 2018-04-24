/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbulb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 01:11:35 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/24 11:14:40 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
/*
static void	rotate(t_mandelbulb *mbulb, t_coord *pt)
{
	double	x0;
	double	y0;

	pt->x = mbulb->cx;
	pt->y = mbulb->cy;
	x0 = pt->x * mbulb->cxy - pt->y * mbulb->sxy;
	pt->y = pt->x * mbulb->sxy + pt->y * mbulb->cxy;
	pt->x = x0;
	x0 = pt->x * mbulb->cxz - pt->z * mbulb->sxz;
	pt->y = pt->x * mbulb->sxz + pt->z * mbulb->cxz;
	pt->x = x0;
	y0 = pt->x * mbulb->cxz - pt->z * mbulb->sxz;
	pt->y = pt->x * mbulb->sxz + pt->z * mbulb->cxz;
	pt->x = x0;
}

static void	mandelbulb2(t_fractol_thread *thread, double i, double j, t_complex c, t_coord pt)
{
	int			iter;
	t_complex	z;
	t_complex	z2;
	t_coord		coord;
	t_coord		tmp;

	iter = 0;
	ft_bzero(&coord, sizeof(t_coord));
	ft_bzero(&tmp, sizeof(t_coord));
	ft_bzero(&z, sizeof(t_complex));
	z = coord;
	z2 = coord;
	while (z2.r + z2.i < 4 && iter < thread->ondraw->max_iter)
	{
		tmp.x = sqrt()
		z.i = 2 * z.r * z.i + c.i;
		z.r = z2.r - z2.i + c.r;
		z2.r = z.r * z.r;
		z2.i = z.i * z.i;
		iter++;
	}
	(*thread->ondraw->draw_point)(thread->ondraw, j, i, iter);
}

static void	calc_angle(t_mandelbulb *mbulb)
{
	mbulb->cxy = cos(mbulb->xy);
	mbulb->cxz = cos(mbulb->xz);
	mbulb->cyz = cos(mbulb->yz);
	mbulb->sxy = sin(mbulb->xy);
	mbulb->sxz = sin(mbulb->xz);
	mbulb->syz = sin(mbulb->yz);
}

void		*mandelbulb(void *ptr)
{
	int					i;
	int					j;
	t_complex			c;
	t_coord				pt;
	t_fractol_thread	*thread;

	thread = (t_fractol_thread*)ptr;
	calc_angle(&thread->ondraw->fractal.mbulb);
	i = thread->y;
	while (i < thread->y_max)
	{
		j = thread->x;
		c.i = (i - FRACTAL_HEIGHT / 2) * thread->ondraw->fractal.mbulb.scale
			+ thread->ondraw->fractal.mbulb.cy;
		while (j < thread->x_max)
		{
			c.r = (j - FRACTAL_WIDTH / 2) * thread->ondraw->fractal.mbulb.scale
				+ thread->ondraw->fractal.mbulb.cx;
			pt.x = c.r;
			pt.y = c.i;
			pt.z = 0.0;
			rotate(&thread->ondraw->fractal.mbulb, &pt);
			mandelbulb2(thread, i, j, c, pt);
			j++;
		}
		i++;
	}
	return (NULL);
}

void		mandelbulb_reset(t_fractal *f)
{
	f->name = "Mandelbulb";
	f->max_iter = 256;
	f->depth = 1;
	f->type = MANDELBULB;
	f->fractal.mandelbulb.cx = 0.0;
	f->fractal.mandelbulb.cy = 0.0;
	f->fractal.mandelbulb.scale = 1.0 / 256;
	f->fractal.mbulb.xy = M_PI;
	f->fractal.mbulb.xz = M_PI;
	f->fractal.mbulb.yz = M_PI * 2;
	f->draw_fractal = &mandelbulb;
	f->reset_fractal = &mandelbulb_reset;
}
*/
