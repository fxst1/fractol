/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_color_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 01:45:16 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/23 09:49:20 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		draw_blue_point(t_fractol *f, t_fractol_thread *thread, int iter)
{
	put_pixel(f->img, thread->x, thread->y, iter * 0xFF / f->max_iteration);
}

void		draw_green_point(t_fractol *f, t_fractol_thread *thread, int iter)
{
	put_pixel(f->img, thread->x, thread->y, (iter * 0xFFFF / f->max_iteration) & 0xFF00);
}

void		draw_red_point(t_fractol *f, t_fractol_thread *thread, int iter)
{
	put_pixel(f->img, thread->x, thread->y, (iter * 0xFFFFFF / f->max_iteration) & 0xFF0000);
}
