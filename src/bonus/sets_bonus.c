/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 03:47:28 by upolat            #+#    #+#             */
/*   Updated: 2024/08/02 01:40:18 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	is_in_julia(t_fractol *f)
{
	int			i;
	t_complex	z;
	t_complex	c;
	double		magnitude_squared;

	i = 0;
	z.real = f->x0;
	z.i = f->y0;
	c.real = f->julia_c_real;
	c.i = f->julia_c_imaginary;
	while (i < f->precision)
	{
		z = ft_complex_sum(ft_complex_square(z), c);
		magnitude_squared = z.real * z.real + z.i * z.i;
		if (magnitude_squared > 4.0)
		{
			i = i * f->mono_color;
			break ;
		}
		i++;
	}
	return (i);
}

int	is_in_mandelbrot(t_fractol *f)
{
	int			i;
	t_complex	z;
	t_complex	c;
	double		magnitude_squared;

	i = 0;
	z.real = 0;
	z.i = 0;
	c.real = f->x0;
	c.i = f->y0;
	while (i < f->precision)
	{
		z = ft_complex_sum(ft_complex_square(z), c);
		magnitude_squared = z.real * z.real + z.i * z.i;
		if (magnitude_squared > 4.0)
		{
			i = i * f->mono_color;
			break ;
		}
		i++;
	}
	return (i);
}

int	is_in_multibrot3(t_fractol *f)
{
	int			i;
	t_complex	z;
	t_complex	c;
	double		magnitude_squared;

	i = 0;
	z.real = 0;
	z.i = 0;
	c.real = f->x0;
	c.i = f->y0;
	while (i < f->precision)
	{
		z = ft_complex_sum(ft_complex_cube(z), c);
		magnitude_squared = z.real * z.real + z.i * z.i;
		if (magnitude_squared > 4.0)
		{
			i = i * f->mono_color;
			break ;
		}
		i++;
	}
	return (i);
}

int	is_in_burning_ship(t_fractol *f)
{
	int			i;
	t_complex	z;
	t_complex	c;
	double		magnitude_squared;

	i = -1;
	z.real = 0;
	z.i = 0;
	c.real = f->x0;
	c.i = f->y0;
	while (++i < f->precision)
	{
		if (z.real < 0)
			z.real = -z.real;
		if (z.i < 0)
			z.i = -z.i;
		z = ft_complex_sum(ft_complex_square(z), c);
		magnitude_squared = z.real * z.real + z.i * z.i;
		if (magnitude_squared > 4.0)
		{
			i = i * f->mono_color;
			break ;
		}
	}
	return (i);
}

int	is_in_phoenix(t_fractol *f)
{
	int			i;
	t_phoenix	p;

	p.epsilon.real = -0.5;
	p.epsilon.i = 0;
	p.c.real = 0.5667;
	p.c.i = 0;
	p.z.real = f->y0;
	p.z.i = f->x0;
	p.z_prev.real = 0;
	p.z_prev.i = 0;
	i = -1;
	while (++i < f->precision)
	{
		p.temp_z = ft_complex_sum(ft_complex_sum(ft_complex_square(p.z), p.c),
				ft_complex_mult(p.epsilon, p.z_prev));
		p.z_prev = p.z;
		p.z = p.temp_z;
		if (p.z.real * p.z.real + p.z.i * p.z.i > 4.0)
			return (i * f->mono_color);
	}
	return (i);
}
