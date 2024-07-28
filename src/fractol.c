/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:29:31 by upolat            #+#    #+#             */
/*   Updated: 2024/07/28 21:09:08 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

float	ft_rand(void)
{
	static unsigned long int	next;

	next = next * 1103515245 + 12345;
	return (((next / 65536) % 32768) / (float)32767);
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	is_in_set(double x0, double y0, t_fractol *f)
{
	int			i;
	t_complex	z;
	t_complex	c;
	double		tmp_real;
	double		magnitude_squared;

	i = 0;
	//z.real = 0;
	//z.i = 0;
	//c.real = x0;
	//c.i = y0;
	z.real = x0;
	z.i = y0;
	c.real = f->julia_c_real;
	c.i = f->julia_c_imaginary;
	while (i < f->precision)
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

uint32_t	color_generator(int i, t_fractol *f)
{
	double	new;
	int		r;
	int		g;
	int		b;

	new = (double)i / 100;
	r = (int)(f->r * new * 4242) % 255;
	g = (int)(f->b * new * 4242) % 255;
	b = (int)(f->g * new * 4242) % 255;
	return (ft_pixel(r, g, b, f->a));
}

void	ft_draw_mandelbrot(void *param)
{
	t_fractol	*f;
	int			i;
	int			j;
	double		x0;
	double		y0;

	f = (t_fractol *)param;
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			x0 = (j - WIDTH / 2) * f->scale;
			y0 = (i - HEIGHT / 2) * f->scale;
			f->color = color_generator(is_in_set(x0, y0, f), f);
			mlx_put_pixel(f->image, j, i, f->color);
			j++;
		}
		i++;
	}
	mlx_image_to_window(f->mlx, f->image, 0, 0);
}

int	initialize_fractol(t_fractol *f)
{
	f->r = ft_rand();
	f->b = ft_rand();
	f->g = ft_rand();
	f->a = 255;
	f->scale = 4.0 / WIDTH;
	f->precision = 100;
	f->julia_c_real = -0.5251993;
	f->julia_c_imaginary = -0.5251993;
	f->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!f->mlx)
		return (EXIT_FAILURE);
	f->image = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (!f->image)
	{
		mlx_close_window(f->mlx);
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(f->mlx, f->image, 0, 0) == -1)
	{
		mlx_close_window(f->mlx);
		return (EXIT_FAILURE);
	}
	return (0);
}

void	ft_keyboard_hooks(mlx_key_data_t k_data, void *vd)
{
	t_fractol *f;

	f = (t_fractol *)vd;
	if (k_data.key == MLX_KEY_Q && k_data.action == MLX_PRESS)
		f->precision *= 1.1;
	if (k_data.key == MLX_KEY_W && k_data.action == MLX_PRESS)
		f->precision *= 0.9;
}

int	main(void)
{
	t_fractol	f;

	initialize_fractol(&f);
	mlx_key_hook(f.mlx, &ft_keyboard_hooks, &f);
	mlx_loop_hook(f.mlx, ft_draw_mandelbrot, &f);
	mlx_loop(f.mlx);
	mlx_terminate(f.mlx);
	return (EXIT_SUCCESS);
}
