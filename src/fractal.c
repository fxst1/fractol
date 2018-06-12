/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 14:48:21 by fxst1             #+#    #+#             */
/*   Updated: 2018/06/12 19:03:27 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char				*fractal_typeid2name(t_fractal_typeid type)
{
	if (type == MANDELBROT)
		return ("Mandelbrot");
	else if (type == JULIA)
		return ("Julia");
	else if (type == BSHIP)
		return ("Burning Ship");
	else
		return (NULL);
}

t_fractal_typeid	fractal_name2typeid(const char *name)
{
	if (!ft_strcmp("mandelbrot", name))
		return (MANDELBROT);
	else if (!ft_strcmp("julia", name))
		return (JULIA);
	else if (!ft_strcmp("bship", name))
		return (BSHIP);
	else
		return (NONE);
}

void				fractal_destroy(t_fractol *prog, t_fractal *f)
{
	if (f && prog->mlx)
	{
		if (f->image)
			mlx_destroy_image(prog->mlx, f->image);
		if (f->window)
			mlx_destroy_window(prog->mlx, f->window);
		free(f);
	}
}

static void			fractal_create_hook(t_fractal *f)
{
	if (f->type == MANDELBROT)
		f->reset_fractal = &mandelbrot_reset;
	else if (f->type == BSHIP)
		f->reset_fractal = &bship_reset;
	else if (f->type == JULIA)
	{
		f->reset_fractal = &julia_reset;
		mlx_hook(f->window, 6, (1L << 6), &mouse_move_hook, f);
	}
	mlx_mouse_hook(f->window, &mouse_hook, f);
	mlx_key_hook(f->window, &key_hook, f);
	(*f->reset_fractal)(f);
}

t_fractal			*fractal_create(t_fractol *prog, t_fractal_typeid type)
{
	t_fractal	*f;

	f = NULL;
	if (type != NONE)
	{
		f = (t_fractal*)malloc(sizeof(t_fractal));
		if (!f)
			fractol_exit(prog, "Cannot allocate fractal: out of memory\n");
		ft_bzero(f, sizeof(t_fractal));
		f->type = type;
		f->prog = prog;
		pthread_mutex_init(&f->mutex, NULL);
		f->name = fractal_typeid2name(type);
		f->draw_point = &psycolors;
		f->filter_name = "Psychedelic";
		f->window = mlx_new_window(prog->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
									f->name);
		if (!f->window)
			fractol_exit(prog, "Cannot create window\n");
		f->image = mlx_new_image(prog->mlx, FRACTAL_WIDTH, FRACTAL_HEIGHT);
		if (!f->image)
			fractol_exit(prog, "Cannot create image\n");
		fractal_create_hook(f);
	}
	return (f);
}
