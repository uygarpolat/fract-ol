/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 03:50:26 by upolat            #+#    #+#             */
/*   Updated: 2024/08/02 14:43:34 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

t_complex	ft_complex_sum(t_complex comp1, t_complex comp2)
{
	t_complex	result;

	result.real = comp1.real + comp2.real;
	result.i = comp1.i + comp2.i;
	return (result);
}

t_complex	ft_complex_square(t_complex comp)
{
	t_complex	result;

	result.real = (comp.real * comp.real) - (comp.i * comp.i);
	result.i = 2 * comp.real * comp.i;
	return (result);
}

t_complex	ft_complex_mult(t_complex comp1, t_complex comp2)
{
	t_complex	result;

	result.real = (comp1.real * comp2.real) - (comp1.i * comp2.i);
	result.i = (comp1.real * comp2.i) + (comp1.i * comp2.real);
	return (result);
}
