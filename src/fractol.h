/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 02:00:36 by upolat            #+#    #+#             */
/*   Updated: 2024/07/29 16:58:04 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
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
	double		scale;
	int			precision;
	int			set_type;
	double		julia_c_real;
	double		julia_c_imaginary;
}				t_fractol;

#endif
