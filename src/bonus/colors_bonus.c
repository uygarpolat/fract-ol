/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 03:40:24 by upolat            #+#    #+#             */
/*   Updated: 2024/08/02 01:39:34 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static float	ft_rand(void)
{
	static unsigned long int	next;

	next = next * 1103515245 + 12345;
	return (((next / 65536) % 32768) / (float)32767);
}

static int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	color_generator(int i, t_fractol *f)
{
	double	new;
	int		r;
	int		g;
	int		b;

	new = (double)i / f->precision;
	r = (int)(f->r * new * 4242) % 255;
	g = (int)(f->g * new * 4242) % 255;
	b = (int)(f->b * new * 4242) % 255;
	return (ft_pixel(r, g, b, f->a));
}

void	get_random_colors(t_fractol *f)
{
	f->r = ft_rand();
	f->g = ft_rand();
	f->b = ft_rand();
}
