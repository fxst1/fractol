/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:37:49 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/24 09:05:46 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <mlx.h>
# include <pthread.h>
# include <fmod.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# define MAX_FRACTAL_TYPEID 4
# define FRACTOL_MAX_THREADS_3D 2
# define FRACTOL_MAX_THREADS_2D 16
# define FRACTOL_MAX_THREADS FRACTOL_MAX_THREADS_2D * FRACTOL_MAX_THREADS_3D
# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000
# define FOOTER_HEIGHT 50
# define FOOTER_WIDTH WINDOW_WIDTH
# define FRACTAL_WIDTH WINDOW_WIDTH
# define FRACTAL_HEIGHT WINDOW_HEIGHT - FOOTER_HEIGHT
# define MAX_ITERATION 500
# define MAX_ZOOM 1000
# define SCALE_Y 0.1
# define SCALE_X 0.1
# define K_MULT 65450
# define K_DIV 65455
# define K_PLUS 65451
# define K_MINUS 65453
# define K_LEFT 65361
# define K_RIGHT 65363
# define K_UP 65362
# define K_DOWN 65364
# define K_ESC 65307
# define K_TAB 65289
# define K_SPACE 32
# define K_R 114
# define M_LEFT 1
# define M_RIGHT 3
# define M_SCROLL_DOWN 4
# define M_SCROLL_UP 6

struct s_fractol;
struct s_fractol_thread;

typedef struct			s_complex
{
	double				r;
	double				i;
}						t_complex;

/*
**	FRACTAL DATA TYPE ID
*/

typedef enum			e_fractal_typeid
{
	NONE,
	MANDELBROT,
	JULIA,
	BSHIP
}						t_fractal_typeid;

/*
**	FRACTAL DATA TYPE ID 1: Mandelbrot
**
**		cx : center x
**		cy : center y
**		scale : zoom
*/

typedef struct			s_mandelbrot
{
	double				cx;
	double				cy;
	double				scale;
}						t_mandelbrot;

/*
**	FRACTAL DATA TYPE ID 2: Julia
**
**		cst:			constant parameter
**		cx:				center x
**		cy:				center y
**		scale:			zoom
*/

typedef struct			s_julia
{
	t_complex			cst;
	double				cx;
	double				cy;
	double				scale;
}						t_julia;

/*
**	FRACTAL DATA TYPE ID 3: BShip
**
**		z_r : center x
**		z_i : center y
**		scale : zoom
*/

typedef struct			s_bship
{
	double				cx;
	double				cy;
	double				scale;
}						t_bship;


/*
**	ALL FRACTAL DATA TYPES
*/

typedef union			s_fractal_data
{
	t_mandelbrot		mandelbrot;
	t_julia				julia;
	t_bship				bship;
}						t_fractal_data;

/*
**	FRACTAL DATA
**
**		type: 			fractal type id
**		fractal: 		parameters
**		name:			name to display into footer
**		filter_name:	name of color filter to display into footer
**		max_iter:		max iteration
**		draw_fractal:	pointer on drawing method
**		reset_fractal:	handler for reset key
**		draw_point:		color filter
**		window:			mlx window (where draw fractal)
**		img:			mlx image (buffer)
*/

typedef struct			s_fractal
{
	t_fractal_typeid	type;
	t_fractal_data		fractal;
	int					enable3d;
	pthread_mutex_t		mutex;
	size_t				running_threads;
	char				*name;
	char				*filter_name;
	int					max_iter;
	int					depth;
	void				*(*draw_fractal)(void*);
	void				(*reset_fractal)(struct s_fractal*);
	void				(*draw_point)(struct s_fractal*, int, int, int);
	void				*window;
	void				*image;
	struct s_fractol	*prog;
}						t_fractal;

/*
**	FRACTAL THREAD
**
**		x:				x coord on plan
**		y:				y coord on plan
**		z:				z coord on plan (3D may enable)
**		x_max:			x_max coord on plan
**		y_max:			y_max coord on plan
**		z_max:			z_max coord on plan (3D may enable)
**		num:			thread id
**		prog:			pointer on main program datas
**		data:			pointer on actual fractal
*/

typedef struct			s_fractol_thread
{
	int					x;
	int					y;
	int					z;
	int					x_max;
	int					y_max;
	int					z_max;
	pthread_t			num;
	struct s_fractol	*prog;
	struct s_fractal	*ondraw;
}						t_fractol_thread;

/*
**	FRACTOL (PROGRAM DATAS)
**
**		mlx:			mlx (from mlx_init)
**		footer_img:		footer black image
**		filter_name:	actual color filter name (see t_fractal)
**		system:			system sound
**		sound:			sound (a good think with auto mode)
*/

typedef struct			s_fractol
{
	pthread_mutex_t		mutex;
	void				*mlx;
	void				*footer_img;
	t_fractal			*fractals[MAX_FRACTAL_TYPEID];

#ifdef		FMOD_ENABLE

	FMOD_SYSTEM			*system;
	FMOD_SOUND			*sound;

#endif

}						t_fractol;

/*
**	MAIN.C
*/

void					usage(void);
void					help(void);


/*
**	FRACTOL.C
*/

void					fractal_draw(t_fractol *prog, t_fractal *f);
int						fractol_draw(void *ptr);
void					fractol_start(t_fractol *prog, char **av);
void					fractol_exit(t_fractol *prog, char *msg);

/*
**	FRACTAL.C
*/

char					*fractal_typeid2name(t_fractal_typeid type);
t_fractal_typeid		fractal_name2typeid(const char *name);
void					fractal_destroy(t_fractol *prog, t_fractal *f);
t_fractal				*fractal_create(t_fractol *prog, t_fractal_typeid type);

/*
**	MANDELBROT.C
*/

void					mandelbrot_reset(t_fractal *f);
void					*mandelbrot(void *ptr);

/*
**	JULIA.C
*/

void					julia_reset(t_fractal *f);
void					*julia(void *ptr);

/*
**	BSHIP.C
*/

void					bship_reset(t_fractal *f);
void					*bship(void *ptr);

/*
**	DRAW_COLOR_POINT.C
*/

void					draw_blue_point(t_fractal *f, int x, int y, int iter);
void					draw_green_point(t_fractal *f, int x, int y, int iter);
void					draw_red_point(t_fractal *f, int x, int y, int iter);

/*
**	PSYCOLORS.C
*/

void					psycolors(t_fractal *f, int x, int y, int iter);

/*
**	GUI
*/

void				refresh_footer(t_fractol *f);
int					refresh_window(void *ptr);
void				put_pixel(void *img, int x, int y, int c);
int					mouse_hook(int button, int x, int y, void *ptr);
int					mouse_move_hook(int x, int y, void *ptr);
int					key_hook(int keycode, void *ptr);
void				stop_fractol(t_fractol *f);
void				start_fmod(t_fractol *f);
void				stop_fmod(t_fractol *f);

/*
**	LIBFT
*/

size_t				ft_strlen(const char *s);
char				*ft_itoa(int n);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_bzero(void *s, size_t len);

#endif
