/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 02:00:36 by upolat            #+#    #+#             */
/*   Updated: 2024/07/31 02:39:02 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <MLX42/MLX42.h>

# define WIDTH	800
# define HEIGHT	800

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
}				t_fractol;

#endif
