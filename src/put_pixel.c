/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 12:56:23 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/23 18:45:46 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel(void *img, int x, int y, int c)
{
	int		bpp;
	int		size_line;
	int		endian;
	char	*data;
	int		*tmp;

	if (x >= 0 && x < FRACTAL_WIDTH && y >= 0 && y < FRACTAL_HEIGHT)
	{
		data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
		tmp = (int*)&data[(y * size_line) + (x * (bpp / 8))];
		*tmp = c;
	}
}
