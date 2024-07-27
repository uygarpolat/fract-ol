/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:29:31 by upolat            #+#    #+#             */
/*   Updated: 2024/07/28 01:59:32 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>

#define WIDTH 800
#define HEIGHT 800

float	ft_rand(void)
{
	static unsigned long int	next;

	next = next * 1103515245 + 12345;
	return (((next / 65536) % 32768) / (float)32767);
}


static mlx_image_t* image;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

typedef struct	s_complex
{
	double	real;
	double	i;
}			t_complex;

typedef struct	s_colors
{
	double	r;
	double	b;
	double	g;
	double	a;
}			t_colors;

int	is_in_set(double x, double y)
{
	int			i;
	int			iterations;
	t_complex	z;
	t_complex	c;
	double		tmp_real;
	double		magnitude_squared;

	i = 0;
	iterations = 100;
	z.real = 0;
	z.i = 0;
	c.real = x;
	c.i = y;
	while (i < iterations)
	{
		tmp_real = z.real * z.real - z.i * z.i + c.real;
		z.i = 2 * z.real * z.i + c.i;
		z.real = tmp_real;
		magnitude_squared = z.real * z.real + z.i * z.i;
		if (magnitude_squared > 4.0)
			break ;
		i++;
	}
	return (i);
}

uint32_t color_generator(int i, t_colors *colors)
{
	double	new;
	int		r;
	int		g;
	int		b;

	new = (double)i / 100;
	r = (int)(colors->r * new * 4242) % 255;
	g = (int)(colors->b * new * 4242) % 255;
	b = (int)(colors->g * new * 4242) % 255;
	return (ft_pixel(r, g, b, 255));
}

void ft_draw_mandelbrot(void* param)
{
	int	i;
	int	j;
	uint32_t	color;
	double scale = 4.0 / WIDTH;
 	double x0, y0;
	t_colors	colors;

	colors.r = ft_rand();
	colors.b = ft_rand();
	colors.g = ft_rand();
	colors.a = 255;

	(void)param;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
		    x0 = (j - WIDTH / 2) * scale;
            y0 = (i - HEIGHT / 2) * scale;
			color = color_generator(is_in_set(x0, y0), &colors);
			mlx_put_pixel(image, j, i, color);
			j++;
		}
		i++;
	}
}

int32_t main(void)
{
	mlx_t* mlx;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	mlx_loop_hook(mlx, ft_draw_mandelbrot, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
