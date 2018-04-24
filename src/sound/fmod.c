/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 23:47:18 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/23 17:09:38 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#ifdef FMOD_ENABLE

void			fmod_start(t_fractol *prog)
{
	FMOD_System_Create(&prog->system);
	FMOD_System_Init(prog->system, 2, FMOD_INIT_NORMAL, NULL);
}

void			fmod_exit(t_fractol *prog)
{
	FMOD_System_Close(prog->system);
	FMOD_System_Release(prog->system);
}

#else

void			fmod_start(t_fractol *prog)
{
	(void)prog;
}

void			fmod_exit(t_fractol *prog)
{
	(void)prog;
}

#endif
