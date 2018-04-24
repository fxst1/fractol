/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 15:17:31 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/24 09:06:42 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		key_mandelbrot(t_fractal *f, int keycode)
{
	if (keycode == K_UP)
		f->fractal.mandelbrot.cy += SCALE_Y;
	else if (keycode == K_DOWN)
		f->fractal.mandelbrot.cy -= SCALE_Y;
	else if (keycode == K_LEFT)
		f->fractal.mandelbrot.cx += SCALE_X;
	else if (keycode == K_RIGHT)
		f->fractal.mandelbrot.cx -= SCALE_X;
	else if (keycode == K_DIV)
		f->fractal.mandelbrot.scale *= 2;
	else if (keycode == K_MULT)
		f->fractal.mandelbrot.scale /= 2;
}

static void		key_julia(t_fractal *f, int keycode)
{
	if (keycode == K_UP)
		f->fractal.julia.cy += SCALE_Y;
	else if (keycode == K_DOWN)
		f->fractal.julia.cy -= SCALE_Y;
	else if (keycode == K_LEFT)
		f->fractal.julia.cx += SCALE_X;
	else if (keycode == K_RIGHT)
		f->fractal.julia.cx -= SCALE_X;
	else if (keycode == K_DIV)
		f->fractal.julia.scale *= 2;
	else if (keycode == K_MULT)
		f->fractal.julia.scale /= 2;
}

static void		key_bship(t_fractal *f, int keycode)
{
	if (keycode == K_UP)
		f->fractal.bship.cy += f->fractal.bship.scale * 2;
	else if (keycode == K_DOWN)
		f->fractal.bship.cy -= f->fractal.bship.scale * 2;
	else if (keycode == K_LEFT)
		f->fractal.bship.cx += f->fractal.bship.scale * 2;
	else if (keycode == K_RIGHT)
		f->fractal.bship.cx -= f->fractal.bship.scale * 2;
	else if (keycode == K_DIV)
		f->fractal.bship.scale *= 2;
	else if (keycode == K_MULT)
		f->fractal.bship.scale /= 2;
}

static void		swap_colors(t_fractal *f)
{
	if (f->draw_point == &psycolors)
		f->draw_point = &draw_red_point;
	else if (f->draw_point == &draw_red_point)
		f->draw_point = &draw_green_point;
	else if (f->draw_point == &draw_green_point)
		f->draw_point = &draw_blue_point;
	else
		f->draw_point = &psycolors;
}

int		key_hook(int keycode, void *ptr)
{
	t_fractal	*f;

	f = (t_fractal*)ptr;
	if (keycode == K_ESC)
		fractol_exit(f->prog, NULL);
	else if (keycode == K_R)
		(*f->reset_fractal)(f);
	else if (keycode == K_SPACE)
		f->enable3d = !f->enable3d;
	else if (keycode == K_MINUS)
		f->max_iter -= 10;
	else if (keycode == K_PLUS)
		f->max_iter += 10;
	else if (keycode == K_TAB)
		swap_colors(f);
	else if (f->type == MANDELBROT)
		key_mandelbrot(f, keycode);
	else if (f->type == JULIA)
		key_julia(f, keycode);
	else if (f->type == BSHIP)
		key_bship(f, keycode);
	fractal_draw(f->prog, f);
	return (0);
}
