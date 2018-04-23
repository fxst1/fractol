/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 15:17:31 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/23 11:53:10 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_out(t_fractol *f)
{
	if (f->zoom / 2 >= 1)
		f->zoom /= 2;
}

void	zoom_in(t_fractol *f)
{
	f->zoom *= 2;
}

void	permutation_colors(t_fractol *f)
{
	if (f->draw_point == &draw_red_point)
	{
		f->filter_name = "1";
		f->draw_point = &draw_blue_point;
	}
	else if (f->draw_point == &draw_blue_point)
	{
		f->filter_name = "2";
		f->draw_point = &draw_green_point;
	}
	else if (f->draw_point == &draw_green_point)
	{
		f->filter_name = "3";
		f->draw_point = &psycolors;
	}
	else
	{
		f->filter_name = "4";
		f->draw_point = &draw_red_point;
	}
}

int		key_hook(int keycode, void *ptr)
{
	t_fractol	*f;

	f = (t_fractol*)ptr;
	//printf("%d\n", keycode);
	if (keycode == K_R)
		(*f->reset_fractal)(f);
	else if (keycode == K_UP)
	{
		f->y1 += SCALE_Y;
		f->y2 += SCALE_Y;
	}
	else if (keycode == K_DOWN)
	{
		f->y1 -= SCALE_Y;
		f->y2 -= SCALE_Y;
	}
	else if (keycode == K_LEFT)
	{
		f->x1 += SCALE_X;
		f->x2 += SCALE_X;
	}
	else if (keycode == K_RIGHT)
	{
		f->x1 -= SCALE_X;
		f->x2 -= SCALE_X;
	}
	else if (keycode == K_DIV)
		zoom_out(f);
	else if (keycode == K_MULT)
		zoom_in(f);
	else if (keycode == K_PLUS)
	{
		f->max_iteration++;
		if (f->max_iteration > MAX_ITERATION)
			f->max_iteration = MAX_ITERATION;
	}
	else if (keycode == K_MINUS)
	{
		if (f->max_iteration > 1)
			f->max_iteration--;
	}
	else if (keycode == K_TAB)
		permutation_colors(f);
	else if (keycode == K_ESC)
		stop_fractol(f);
	return (0);
}
