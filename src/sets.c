/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 03:47:28 by upolat            #+#    #+#             */
/*   Updated: 2024/07/31 03:48:02 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	is_in_julia(t_fractol *f)
{
	int			i;
	t_complex	z;
	t_complex	c;
	double		magnitude_squared;

	i = 0;
	z.real = f->x0;
	z.i = -f->y0;
	c.real = f->julia_c_real;
	c.i = f->julia_c_imaginary;
	while (i < f->precision)
	{
		z = ft_complex_sum(ft_complex_square(z), c);
		magnitude_squared = z.real * z.real + z.i * z.i;
		if (magnitude_squared > 4.0)
			break ;
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
			break ;
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
			break ;
		i++;
	}
	return (i);
}

int	is_in_burning_ship(t_fractol *f)
{
	int			i;
	t_complex	z;
	t_complex	c;
	double		tmp_real;
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
		tmp_real = z.real * z.real - z.i * z.i + c.real;
		z.i = 2 * z.real * z.i + c.i;
		z.real = tmp_real;
		magnitude_squared = z.real * z.real + z.i * z.i;
		if (magnitude_squared > 4.0)
			break ;
	}
	return (i);
}
