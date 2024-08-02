/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:29:31 by upolat            #+#    #+#             */
/*   Updated: 2024/08/02 14:22:16 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	print_usage(void)
{
	ft_putstr_fd("------------------------------------------------------\n", 1);
	ft_putstr_fd("Usage:\n", 1);
	ft_putstr_fd("Please enter a valid set name: ", 1);
	ft_putstr_fd("Mandelbrot, Julia\n", 1);
	ft_putstr_fd("Julia needs real and imaginary parts as input.\n", 1);
	ft_putstr_fd("Example: ./fractol Mandelbrot\n", 1);
	ft_putstr_fd("Example: ./fractol Julia -0.5251993 -0.5251993\n", 1);
	ft_putstr_fd("Use arrow keys to move, use scroll to zoom in and out.\n", 1);
	ft_putstr_fd("Increase precision: Q\n", 1);
	ft_putstr_fd("Decrease precision: W\n", 1);
	ft_putstr_fd("Change color palate: C\n", 1);
	ft_putstr_fd("Toggle single color for better view of the set: M\n", 1);
	ft_putstr_fd("Toggle DISCO mode: D\n", 1);
	ft_putstr_fd("Reset selections: R\n", 1);
	ft_putstr_fd("End program: ESC\n", 1);
	ft_putstr_fd("------------------------------------------------------\n", 1);
	exit(1);
}

static void	draw_fractals(void *param)
{
	t_fractol	*f;
	int			i;
	int			j;

	f = (t_fractol *)param;
	if (f->disco_mode > 0)
		get_random_colors(f);
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			f->y0 = (HEIGHT - i) * (f->y_max - f->y_min) / HEIGHT + f->y_min;
			f->x0 = j * (f->x_max - f->x_min) / WIDTH + f->x_min;
			f->color = color_generator(f->func(f), f);
			mlx_put_pixel(f->image, j, i, f->color);
			j++;
		}
		i++;
	}
	mlx_image_to_window(f->mlx, f->image, 0, 0);
}

static void	set_values(t_fractol *f)
{
	f->a = 255;
	f->disco_mode = -1;
	f->mono_color = 1;
	f->precision = 100;
	f->zoom = 1;
	f->x_max = 2;
	f->y_max = 2;
	f->x_min = -2;
	f->y_min = -2;
}

int	initialize_fractol(t_fractol *f)
{
	get_random_colors(f);
	set_values(f);
	f->mlx = mlx_init(WIDTH, HEIGHT, "Fractol", true);
	if (!f->mlx)
		return (1);
	f->image = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (!f->image)
	{
		mlx_close_window(f->mlx);
		mlx_terminate(f->mlx);
		return (1);
	}
	if (mlx_image_to_window(f->mlx, f->image, 0, 0) == -1)
	{
		mlx_delete_image(f->mlx, f->image);
		mlx_close_window(f->mlx);
		mlx_terminate(f->mlx);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_fractol	f;

	if (!validity_check(&f, argc, argv))
		print_usage();
	if (initialize_fractol(&f))
		return (1);
	mlx_key_hook(f.mlx, &keyboard_hooks, &f);
	mlx_close_hook(f.mlx, &close_hook, &f);
	mlx_scroll_hook(f.mlx, &scroll_hook, &f);
	mlx_loop_hook(f.mlx, draw_fractals, &f);
	mlx_loop(f.mlx);
	mlx_terminate(f.mlx);
	return (0);
}
