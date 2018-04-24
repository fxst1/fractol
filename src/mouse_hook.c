/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 10:58:06 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/24 13:29:36 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		mouse_mandelbrot(int button, int x, int y, t_fractal *f)
{
//	printf("button =  %d\n", button);
	if (button != M_LEFT && button != M_RIGHT)
		return ;
	f->fractal.mandelbrot.cx += (x - FRACTAL_WIDTH / 2) *
								f->fractal.mandelbrot.scale;
	f->fractal.mandelbrot.cy += ((y - FRACTAL_HEIGHT / 2) *
								f->fractal.mandelbrot.scale) / 2;
	if (button == M_LEFT)
		f->fractal.mandelbrot.scale /= 2;
	else if (button == M_RIGHT)
		f->fractal.mandelbrot.scale *= 2;
	(void)x;
	(void)y;
}

static void		mouse_julia(int button, int x, int y, t_fractal *f)
{
	printf("button =  %d\n", button);
	if (button != M_LEFT && button != M_RIGHT)
		return ;
	f->fractal.julia.cx += (x - FRACTAL_WIDTH / 2) *
								f->fractal.julia.scale;
	f->fractal.julia.cy += ((y - FRACTAL_HEIGHT / 2) *
								f->fractal.julia.scale) / 2;
	if (button == M_LEFT)
		f->fractal.julia.scale /= 2;
	else if (button == M_RIGHT)
		f->fractal.julia.scale *= 2;
	(void)x;
	(void)y;
}

static void		mouse_bship(int button, int x, int y, t_fractal *f)
{
	printf("button =  %d\n", button);
	if (button != M_LEFT && button != M_RIGHT)
		return ;
	else if (button == M_LEFT)
	{
		f->fractal.bship.cx += (x - FRACTAL_WIDTH / 2) *
									f->fractal.bship.scale;
		f->fractal.bship.cy += ((y - FRACTAL_HEIGHT / 2) *
									f->fractal.bship.scale) / 2;
		f->fractal.bship.scale /= 2;
	}
	else if (button == M_RIGHT)
	{
		f->fractal.bship.cx += (x - FRACTAL_WIDTH / 2) *
									f->fractal.bship.scale;
		f->fractal.bship.cy -= ((y - FRACTAL_HEIGHT / 2) *
									f->fractal.bship.scale);
		f->fractal.bship.scale *= 2;
	}
	(void)x;
	(void)y;
}

int				mouse_move_hook(int x, int y, void *ptr)
{
	t_fractal	*f;

	f = (t_fractal*)ptr;
	if (f->type == JULIA && x >= 0 && x < FRACTAL_WIDTH &&
							y >= 0 && y < FRACTAL_HEIGHT)
	{
		f->fractal.julia.cst.r = (x - FRACTAL_WIDTH / 2) *
								f->fractal.julia.scale + f->fractal.julia.cx;
		f->fractal.julia.cst.i = (y - FRACTAL_HEIGHT / 2) *
								f->fractal.julia.scale + f->fractal.julia.cy;
		fractal_draw(f->prog, f);
	}
	return (0);
	(void)x;
	(void)y;
}

int				mouse_hook(int button, int x, int y, void *ptr)
{
	t_fractal	*f;

	f = (t_fractal*)ptr;
	if (x >= 0 && x < FRACTAL_WIDTH && y >= 0 && y < FRACTAL_HEIGHT)
	{
		if (f->type == MANDELBROT)
			mouse_mandelbrot(button, x, y, f);
		else if (f->type == JULIA)
			mouse_julia(button, x, y, f);
		else if (f->type == BSHIP)
			mouse_bship(button, x, y, f);
	}
	fractal_draw(f->prog, f);
	return (0);
}
