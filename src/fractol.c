/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:29:31 by upolat            #+#    #+#             */
/*   Updated: 2024/07/29 17:00:51 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_close(t_fractol *f, int exitcode)
{
	if (f->image)
		mlx_delete_image(f->mlx, f->image);
	if (f->mlx)
	{
		mlx_close_window(f->mlx);
		mlx_terminate(f->mlx);
	}
	exit(exitcode);
}

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

void	choose_set(t_fractol *f, t_complex *z, t_complex *c)
{
	if (f->set_type == 1)
	{
		z->real = 0;
		z->i = 0;
		c->real = f->x0;
		c->i = f->y0;
	}
	else if (f->set_type == 2)
	{
		z->real = f->x0;
		z->i = f->y0;
		c->real = f->julia_c_real;
		c->i = f->julia_c_imaginary;
	}
}

int	is_in_set(t_fractol *f)
{
	int			i;
	t_complex	z;
	t_complex	c;
	double		tmp_real;
	double		magnitude_squared;

	i = 0;
	choose_set(f, &z, &c);
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
	g = (int)(f->g * new * 4242) % 255;
	b = (int)(f->b * new * 4242) % 255;
	return (ft_pixel(r, g, b, f->a));
}

void	ft_draw_mandelbrot(void *param)
{
	t_fractol	*f;
	int			i;
	int			j;

	f = (t_fractol *)param;
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			f->x0 = (j - WIDTH / 2) * f->scale;
			f->y0 = (i - HEIGHT / 2) * f->scale;
			f->color = color_generator(is_in_set(f), f);
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
	f->g = ft_rand();
	f->b = ft_rand();
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

void	ft_keyboard_hooks(mlx_key_data_t k_data, void *arg)
{
	t_fractol	*f;

	f = (t_fractol *)arg;
	if (k_data.key == MLX_KEY_Q && k_data.action == MLX_PRESS)
		f->precision *= 1.1;
	if (k_data.key == MLX_KEY_W && k_data.action == MLX_PRESS)
		f->precision *= 0.9;
	if (k_data.key == MLX_KEY_ESCAPE && k_data.action == MLX_PRESS)
		ft_close(f, 0);
	if (k_data.key == MLX_KEY_C && k_data.action == MLX_PRESS)
	{
		f->r = ft_rand();
		f->g = ft_rand();
		f->b = ft_rand();
	}
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	return (0);
}

int	validity_check(t_fractol *f, int argc, char **argv)
{
	if (argc == 2 && !ft_strcmp(argv[1], "mandelbrot"))
		f->set_type = 1;
	else if (argc == 4 && !ft_strcmp(argv[1], "julia"))
		f->set_type = 2;
	else
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_fractol	f;

	if (!validity_check(&f, argc, argv))
		return (printf("Usage:\n"), 1);
	initialize_fractol(&f);
	mlx_key_hook(f.mlx, &ft_keyboard_hooks, &f);
	mlx_loop_hook(f.mlx, ft_draw_mandelbrot, &f);
	mlx_loop(f.mlx);
	mlx_terminate(f.mlx);
	return (EXIT_SUCCESS);
}
