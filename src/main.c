/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 23:21:42 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/23 11:50:19 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		usage(void)
{
	write(STDOUT_FILENO, "[mandelbrot|julia|bs]\n", 22);
}

static void		start_process(t_fractol *f)
{
	pthread_mutex_init(&f->mutex, NULL);
	f->mlx = mlx_init();
	f->window = mlx_new_window(f->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Fractol");
	f->img = mlx_new_image(f->mlx, FRACTAL_WIDTH, FRACTAL_HEIGHT);
	f->footer_img = mlx_new_image(f->mlx, FOOTER_WIDTH, FOOTER_HEIGHT);
	f->draw_point = &psycolors;
	f->filter_name = "3";
	f->max_iteration = MAX_ITERATION - 1;
	mlx_mouse_hook(f->window, &mouse_hook, f);
	mlx_key_hook(f->window, &key_hook, f);
	mlx_loop_hook(f->mlx, &refresh_window, f);
}

int				main(int ac, char **av)
{
	t_fractol	f;

	bzero(&f, sizeof(t_fractol));
	if (ac != 2)
	{
		usage();
		return (1);
	}
	else if (!ft_strcmp("mandelbrot", av[1]))
		mandelbrot_reset(&f);
	else
	{
		usage();
		return (1);
	}
	start_process(&f);
	mlx_loop(f.mlx);
	return (0);
	(void)ac;
	(void)av;
}
