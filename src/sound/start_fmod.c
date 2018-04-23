/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_fmod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 23:47:18 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/21 00:38:43 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			start_fmod(t_fractol *f)
{
	FMOD_System_Create(&f->system);
	FMOD_System_Init(f->system, 2, FMOD_INIT_NORMAL, NULL);
}
