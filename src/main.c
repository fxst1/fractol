/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 23:21:42 by fxst1             #+#    #+#             */
/*   Updated: 2018/06/12 19:08:23 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			usage(void)
{
	int		i;

	i = write(STDOUT_FILENO, "[mandelbrot|julia|bship]\n", 25);
	(void)i;
}

int				main(int ac, char **av)
{
	t_fractol	prog;

	ft_bzero(&prog, sizeof(t_fractol));
	if (ac < 2)
	{
		usage();
		return (1);
	}
	fractol_start(&prog, av + 1);
	fractol_draw(&prog);
	mlx_loop(prog.mlx);
	return (0);
	(void)ac;
	(void)av;
}
