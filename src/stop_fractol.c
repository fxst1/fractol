/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_fractol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 08:46:04 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/23 12:15:34 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		stop_fractol(t_fractol *f)
{
	mlx_destroy_image(f->mlx, f->img);
	mlx_destroy_image(f->mlx, f->footer_img);
	mlx_destroy_window(f->mlx, f->window);
	exit(EXIT_SUCCESS);
}
