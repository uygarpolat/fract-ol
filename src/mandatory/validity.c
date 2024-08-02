/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 01:29:04 by upolat            #+#    #+#             */
/*   Updated: 2024/08/02 02:38:49 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	double_validity_check(char *str)
{
	int	i;
	int	dot_counter;

	dot_counter = 0;
	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == '.')
		return (0);
	if (!(str[0] <= '9' && str[0] >= '0')
		&& str[0] != '.' && str[0] != '+' && str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == '.')
			dot_counter++;
		if (dot_counter > 1)
			return (0);
		if (!(str[i] <= '9' && str[i] >= '0') && str[i] != '.')
			return (0);
		if (i > 0 && (str[i]))
			i++;
	}
	return (1);
}

int	validity_check(t_fractol *f, int argc, char **argv)
{
	if (argc == 2)
	{
		if (!ft_strcmp(argv[1], "Mandelbrot"))
			f->func = &is_in_mandelbrot;
		else
			return (0);
	}
	else if (argc == 4 && !ft_strcmp(argv[1], "Julia"))
	{
		if (!double_validity_check(argv[2]) || !double_validity_check(argv[3]))
			return (0);
		f->julia_c_real = ft_atold(argv[2]);
		f->julia_c_imaginary = ft_atold(argv[3]);
		f->func = &is_in_julia;
	}
	else
		return (0);
	return (1);
}
