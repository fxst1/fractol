/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:06:30 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/24 13:19:55 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		fractal_draw(t_fractol *prog, t_fractal *f)
{
	t_fractol_thread	threads[FRACTOL_MAX_THREADS];
	int					start_x;
	int					end_x;
	int					n;
	int					z;

	z = 0;
	n = 0;
	while (z <= f->depth)
	{
		start_x = 0;
		end_x = FRACTAL_WIDTH / FRACTOL_MAX_THREADS_2D;
		while (end_x <= FRACTAL_WIDTH)
		{
			threads[n].prog = prog;
			threads[n].ondraw = f;
			threads[n].x = start_x;
			threads[n].y = 0;
			threads[n].z = z;
			threads[n].x_max = end_x;
			threads[n].y_max = FRACTAL_HEIGHT;
			threads[n].z_max = z + 1;
			start_x = end_x;
			end_x += FRACTAL_WIDTH / FRACTOL_MAX_THREADS_2D;
			pthread_create(&threads[n].num, NULL, f->draw_fractal,
				&threads[n]);
			n++;
		}
		z++;
	}
	while (--n)
		pthread_join(threads[n].num, NULL);
	mlx_put_image_to_window(prog->mlx, f->window, f->image, 0, 0);
}

int			fractol_draw(void *ptr)
{
	t_fractal_typeid	type;
	t_fractol			*prog;

	type = 1;
	prog = (t_fractol*)ptr;
	while (type < MAX_FRACTAL_TYPEID)
	{
		if (prog->fractals[type] != NULL)
			fractal_draw(prog, prog->fractals[type]);
		type++;
	}
	return (0);
}

void		fractol_start(t_fractol *prog, char **av)
{
	t_fractal_typeid	type;

	prog->mlx = mlx_init();
	if (!prog->mlx)
		fractol_exit(prog, "Cannot init mlx\n");
	prog->footer_img = mlx_new_image(prog->mlx, FOOTER_WIDTH, FOOTER_HEIGHT);
	while (*av)
	{
		type = fractal_name2typeid(*av);
		if (type == NONE)
		{
			usage();
			fractol_exit(prog, "Unexisting fractal\n");
		}
		else if (prog->fractals[type] != NULL)
		{
			usage();
			fractol_exit(prog, "Multiple fractal error\n");
		}
		prog->fractals[type] = fractal_create(prog, type);
		av++;
	}
	mlx_expose_hook(prog->mlx, &fractol_draw, prog);
}


void		fractol_exit(t_fractol *prog, char *msg)
{
	t_fractal_typeid		type;
	int						i;

	i = 0;
	type = 1;
	while (type < MAX_FRACTAL_TYPEID)
	{
		if (prog->fractals[type] != NULL)
			fractal_destroy(prog, prog->fractals[type]);
		type++;
	}
	if (msg)
		i = write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(i > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}
