/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 00:11:19 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/23 13:33:02 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int				refresh_fractal(t_fractol *f)
{
	int					start_x;
	int					end_x;
	int					n;

	start_x = 0;
	end_x = FRACTAL_WIDTH / FRACTOL_MAX_THREADS;
	n = 0;
	f->ended_threads = 0;
	while (end_x <= FRACTAL_WIDTH)
	{
		f->thread_data[n].data = f;
		f->thread_data[n].x = start_x;
		f->thread_data[n].y = 0;
		f->thread_data[n].x_max = end_x;
		f->thread_data[n].y_max = FRACTAL_HEIGHT;
		start_x = end_x;
		end_x += FRACTAL_WIDTH / FRACTOL_MAX_THREADS;
		pthread_create(&f->thread_data[n].num, NULL, f->draw_fractal,
							&f->thread_data[n]);
		n++;
	}
	while (--n)
		pthread_join(f->thread_data[n].num, NULL);
	mlx_put_image_to_window(f->mlx, f->window, f->img, 0, 0);
	return (n);

}

void					refresh_axis(t_fractol *f)
{
	int					x;
	int					y;

	x = -100;
	while (x <= 100)
	{
		y = -100;
		while (y <= 100)
		{
			mlx_pixel_put(f->mlx, f->window, x, y, 0xFFFFFF);
			y += 10;
		}
		x += 10;
	}
}

void					refresh_footer(t_fractol *f)
{
	char				*tmp;

	mlx_put_image_to_window(f->mlx, f->window, f->footer_img,
								0, WINDOW_HEIGHT - FOOTER_HEIGHT);
	mlx_string_put(f->mlx, f->window, 10, WINDOW_HEIGHT - FOOTER_HEIGHT + 15,
					0xffffff, "Fractal");
	mlx_string_put(f->mlx, f->window, 160, WINDOW_HEIGHT - FOOTER_HEIGHT + 15,
					0xffffff, "X");
	mlx_string_put(f->mlx, f->window, 310, WINDOW_HEIGHT - FOOTER_HEIGHT + 15,
					0xffffff, "Y");
	mlx_string_put(f->mlx, f->window, 460, WINDOW_HEIGHT - FOOTER_HEIGHT + 15,
					0xffffff, "Zoom");
	mlx_string_put(f->mlx, f->window, 610, WINDOW_HEIGHT - FOOTER_HEIGHT + 15,
					0xffffff, "Iterations");
	mlx_string_put(f->mlx, f->window, 760, WINDOW_HEIGHT - FOOTER_HEIGHT + 15,
					0xffffff, "Filter");
	mlx_string_put(f->mlx, f->window, 10, WINDOW_HEIGHT - FOOTER_HEIGHT + 35,
					0xffffff, f->fractal_name);
	tmp = ft_itoa(f->x1);
	mlx_string_put(f->mlx, f->window, 160, WINDOW_HEIGHT - FOOTER_HEIGHT + 35,
					0xffffff, tmp);
	free(tmp);
	tmp = ft_itoa(f->y1);
	mlx_string_put(f->mlx, f->window, 310, WINDOW_HEIGHT - FOOTER_HEIGHT + 35,
					0xffffff, tmp);
	free(tmp);
	tmp = ft_itoa(f->zoom);
	mlx_string_put(f->mlx, f->window, 460, WINDOW_HEIGHT - FOOTER_HEIGHT + 35,
					0xffffff, tmp);
	free(tmp);
	tmp = ft_itoa(f->max_iteration);
	mlx_string_put(f->mlx, f->window, 610, WINDOW_HEIGHT - FOOTER_HEIGHT + 35,
					0xffffff, tmp);
	free(tmp);
	mlx_string_put(f->mlx, f->window, 760, WINDOW_HEIGHT - FOOTER_HEIGHT + 35,
					0xffffff, f->filter_name);
}

int						refresh_window(void *ptr)
{
	t_fractol 			*f;

	f = (t_fractol*)ptr;
	refresh_fractal(f);
	refresh_footer(f);
	refresh_axis(f);
	return (0);
}
