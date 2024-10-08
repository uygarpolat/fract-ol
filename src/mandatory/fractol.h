/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 02:00:36 by upolat            #+#    #+#             */
/*   Updated: 2024/08/03 15:14:39 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <MLX42/MLX42.h>

# define WIDTH	1200
# define HEIGHT	1200

typedef struct s_complex
{
	double	real;
	double	i;
}			t_complex;

typedef struct s_fractol
{
	mlx_image_t	*image;
	mlx_t		*mlx;
	uint32_t	color;
	double		r;
	double		g;
	double		b;
	double		a;
	double		x0;
	double		y0;
	double		x_max;
	double		y_max;
	double		x_min;
	double		y_min;
	int			precision;
	double		julia_c_real;
	double		julia_c_imaginary;
	int			(*func)(struct s_fractol *f);
	int			disco_mode;
	double		zoom;
	int			mono_color;
}				t_fractol;

// Hooks
void		close_hook(void *arg);
void		keyboard_hooks(mlx_key_data_t k_data, void *arg);
void		scroll_hook(double xdelta, double ydelta, void *arg);

// Colors
uint32_t	color_generator(int i, t_fractol *f);
void		get_random_colors(t_fractol *f);

// Sets
int			is_in_mandelbrot(t_fractol *f);
int			is_in_julia(t_fractol *f);

// Complex arithmetic
t_complex	ft_complex_sum(t_complex comp1, t_complex comp2);
t_complex	ft_complex_square(t_complex comp);

// Utils
int			initialize_fractol(t_fractol *f);
void		ft_putstr_fd(char *s, int fd);
long double	ft_atold(const char *s);
int			ft_strcmp(char *str1, char *str2);
int			validity_check(t_fractol *f, int argc, char **argv);

#endif
