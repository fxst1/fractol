/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 10:58:06 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/23 11:27:59 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		mouse_zoom_in(t_fractol *f, int x, int y)
{
	if (f->zoom * 1.2 > MAX_ZOOM)
		return ;
	f->x1 += x / 5;
	f->y1 += y / 5;
	f->x1 *= 1.2;
	f->y1 *= 1.2;
	f->zoom *= 1.2;
}

static void		mouse_zoom_out(t_fractol *f, int x, int y)
{
	if (f->zoom / 1.2 < 1)
		return ;
	f->x1 -= x / 5;
	f->y1 -= y / 5;
	f->x1 /= 1.2;
	f->y1 /= 1.2;
	f->zoom /= 1.2;
}

static void		mouse_fractal(int button, int x, int y, t_fractol *f)
{
	printf("%d (%d - %d)\n", button, x, y);
	if (button == M_SCROLL_DOWN)
		mouse_zoom_in(f, x, y);
	else if (button == M_SCROLL_UP)
		mouse_zoom_out(f, x, y);
	(void)f;
}

int		mouse_hook(int button, int x, int y, void *ptr)
{
	t_fractol	*f;

	f = (t_fractol*)ptr;
	if (x >= 0 && x < FRACTAL_WIDTH && y >= 0 && y < FRACTAL_HEIGHT)
		mouse_fractal(button, x, y, f);
	return (0);
}
