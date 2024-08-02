/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 03:34:52 by upolat            #+#    #+#             */
/*   Updated: 2024/08/02 01:40:09 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	close_hook(void *arg)
{
	t_fractol	*f;

	f = (t_fractol *)arg;
	if (f->image)
		mlx_delete_image(f->mlx, f->image);
	if (f->mlx)
	{
		mlx_close_window(f->mlx);
		mlx_terminate(f->mlx);
	}
	exit(0);
}

static void	up_down_left_right_hooks(mlx_key_data_t k_data, t_fractol *f)
{
	if (k_data.key == MLX_KEY_UP && k_data.action == MLX_PRESS)
	{
		f->y_max += 0.1 * f->zoom;
		f->y_min += 0.1 * f->zoom;
	}
	if (k_data.key == MLX_KEY_DOWN && k_data.action == MLX_PRESS)
	{
		f->y_max -= 0.1 * f->zoom;
		f->y_min -= 0.1 * f->zoom;
	}
	if (k_data.key == MLX_KEY_LEFT && k_data.action == MLX_PRESS)
	{
		f->x_max += 0.1 * f->zoom;
		f->x_min += 0.1 * f->zoom;
	}
	if (k_data.key == MLX_KEY_RIGHT && k_data.action == MLX_PRESS)
	{
		f->x_max -= 0.1 * f->zoom;
		f->x_min -= 0.1 * f->zoom;
	}
}

static void	reset_selections(mlx_key_data_t k_data, t_fractol *f)
{
	if (k_data.key == MLX_KEY_R && k_data.action == MLX_PRESS)
	{
		f->disco_mode = -1;
		f->mono_color = 1;
		f->precision = 100;
		f->zoom = 1;
		f->x_max = 2;
		f->y_max = 2;
		f->x_min = -2;
		f->y_min = -2;
	}
}

void	keyboard_hooks(mlx_key_data_t k_data, void *arg)
{
	t_fractol	*f;

	f = (t_fractol *)arg;
	if (k_data.key == MLX_KEY_Q && k_data.action == MLX_PRESS)
		f->precision *= 1.1;
	if (k_data.key == MLX_KEY_W && k_data.action == MLX_PRESS)
		f->precision *= 0.9;
	if (k_data.key == MLX_KEY_ESCAPE && k_data.action == MLX_PRESS)
		close_hook(f);
	if (k_data.key == MLX_KEY_C && k_data.action == MLX_PRESS)
		get_random_colors(f);
	if (k_data.key == MLX_KEY_D && k_data.action == MLX_PRESS)
		f->disco_mode *= -1;
	if (k_data.key == MLX_KEY_M && k_data.action == MLX_PRESS)
		f->mono_color = (f->mono_color + 1) % 2;
	reset_selections(k_data, f);
	up_down_left_right_hooks(k_data, f);
}

void	scroll_hook(double xdelta, double ydelta, void *arg)
{
	t_fractol	*f;
	t_complex	offset;
	double		coefficient;
	int32_t		mouse_x;
	int32_t		mouse_y;

	(void) xdelta;
	f = (t_fractol *)arg;
	if (ydelta != 0)
	{
		mlx_get_mouse_pos(f->mlx, &mouse_x, &mouse_y);
		if (ydelta > 0)
			coefficient = 1.1;
		else
			coefficient = 0.9;
		f->zoom *= coefficient;
		offset.real = (mouse_x * (f->x_max - f->x_min)
				/ WIDTH + f->x_min) * (1 - coefficient);
		offset.i = ((HEIGHT - mouse_y) * (f->y_max - f->y_min)
				/ HEIGHT + f->y_min) * (1 - coefficient);
		f->x_max = f->x_max * coefficient + offset.real;
		f->x_min = f->x_min * coefficient + offset.real;
		f->y_max = f->y_max * coefficient + offset.i;
		f->y_min = f->y_min * coefficient + offset.i;
	}
}
