/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_color_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 01:45:16 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/23 18:14:29 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		draw_blue_point(t_fractal *f, int x, int y, int iter)
{
	put_pixel(f->image, x, y, iter * 0xFF / f->max_iter);
}

void		draw_green_point(t_fractal *f, int x, int y, int iter)
{
	put_pixel(f->image, x, y, (iter * 0xFFFF / f->max_iter) & 0xFF00);
}

void		draw_red_point(t_fractal *f, int x, int y, int iter)
{
	put_pixel(f->image, x, y, (iter * 0xFFFFFF / f->max_iter) & 0xFF0000);
}
