#ifndef FRACTOL_H
# define FRACTOL_H
# include <mlx.h>
# include <pthread.h>
# include <fmod.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# define FRACTOL_MAX_THREADS 128
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1000
# define FOOTER_HEIGHT 50
# define FOOTER_WIDTH WINDOW_WIDTH
# define FRACTAL_WIDTH WINDOW_WIDTH
# define FRACTAL_HEIGHT WINDOW_HEIGHT - FOOTER_HEIGHT
# define MAX_ITERATION 500
# define MAX_ZOOM 1000
# define SCALE_Y 0.5
# define SCALE_X 0.5
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
# define M_SCROLL_DOWN 4
# define M_SCROLL_UP 6

struct s_fractol;
struct s_fractol_thread;

typedef enum			e_fractol_enum
{
	JULIA,
	MENDELBROT
}						t_fractol_enum;

typedef struct			s_console
{
	char				*command;
	size_t				cursor;
	size_t				length;
	void				*img;
}						t_console;

typedef struct			s_egalizer
{
	float				data[256];
	void				*img;
}						t_egalizer;

typedef struct			s_fractol_thread
{
	int					x;
	int					y;
	int					x_max;
	int					y_max;
	pthread_t			num;
	struct s_fractol	*data;
}						t_fractol_thread;

typedef struct			s_fractol
{
	t_fractol_thread	thread_data[FRACTOL_MAX_THREADS];
	int					ended_threads;
	pthread_mutex_t		mutex;

	FMOD_SYSTEM			*system;
	FMOD_SOUND			*sound;

	void				*mlx;
	void				*window;
	void				*img;

	void				*footer_img;

	t_console			console;
	t_egalizer			egalizer;

	int					max_iteration;
	double				x1;
	double				x2;
	double				y1;
	double				y2;
	double				zoom;

	char				*fractal_name;
	char				*filter_name;

	void				*(*draw_fractal)(void*);
	void				(*reset_fractal)(struct s_fractol*);
	void				(*draw_point)(struct s_fractol*,
										struct s_fractol_thread*,
										int);
}						t_fractol;

/*
**	FRACTALS
*/

void				mandelbrot_reset(t_fractol *f);
void				*mandelbrot(void *ptr);

/*
**	COLORS
*/

void				draw_blue_point(t_fractol *f, t_fractol_thread *thread,
									int iter);
void				draw_green_point(t_fractol *f, t_fractol_thread *thread,
									int iter);
void				draw_red_point(t_fractol *f, t_fractol_thread *thread,
									int iter);
void				psycolors(t_fractol *f, t_fractol_thread *thread, int iter);

/*
**	GUI
*/

void				refresh_footer(t_fractol *f);
int					refresh_window(void *ptr);
void				put_pixel(void *img, int x, int y, int c);
int					mouse_hook(int button, int x, int y, void *ptr);
int					key_hook(int keycode, void *ptr);
void				stop_fractol(t_fractol *f);
void				start_fmod(t_fractol *f);
void				stop_fmod(t_fractol *f);

/*
**	LIBFT
*/

char				*ft_itoa(int n);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_bzero(void *s, size_t len);

#endif
