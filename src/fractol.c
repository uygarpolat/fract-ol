/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:29:31 by upolat            #+#    #+#             */
/*   Updated: 2024/07/30 17:30:05 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	print_usage(void)
{
	ft_putstr_fd("Usage:\nFirst argument has to be one of those sets: ", 1);
	ft_putstr_fd("Mandelbrot, Julia.\n", 1);
	ft_putstr_fd("In case the Julia set was choosen provide two additional ", 1);
	ft_putstr_fd("parameters: the real and imaginary parts of C.\n", 1);
	ft_putstr_fd("To move the view use arrows, to zoom in and out use scroll.\n", 1);
	ft_putstr_fd("To increase precision press Q to decrease it press W.\n", 1);
	ft_putstr_fd("To change colour palette press C.\n", 1);
	exit (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_isspace(const char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	nbr;

	sign = 1;
	nbr = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		sign = -sign;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (sign == 1 && (nbr > (LONG_MAX - (*str - '0')) / 10))
			return (-1);
		else if (sign == -1 && (-nbr < (LONG_MIN + (*str - '0')) / 10))
			return (0);
		nbr = nbr * 10 + *str - '0';
		str++;
	}
	return (sign * nbr);
}

long double	ft_atold(const char *s)
{
	char		*str;
	long double	int_part;
	long double	float_part;
	int			i;
	int			sign;

	sign = 1;
	str = (char *) s;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '+' || *str == '-')
		str++;
	int_part = (long double)ft_atoi(str);
	while (*str && *str != '.')
		str++;
	if (*str == '.')
		str++;
	float_part = (long double)ft_atoi(str);
	i = ft_strlen(str);
	while (i--)
		float_part /= 10;
	return (sign * (int_part + float_part));
}

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

t_complex	ft_complex_cube(t_complex comp)
{
	t_complex	result;

	result.real = (comp.real * comp.real * comp.real)
		- 3 * (comp.real * comp.i * comp.i);
	result.i = 3 * (comp.real * comp.real * comp.i)
		- (comp.i * comp.i * comp.i);
	return (result);
}

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
	static unsigned long int	next = 5;

	next = next * 1103515245 + 12345;
	return (((next / 65536) % 32768) / (float)32767);
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

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

void	draw_fractals(void *param)
{
	t_fractol	*f;
	int			i;
	int			j;

	f = (t_fractol *)param;
	i = 0;
	if (f->disco_mode > 0)
	{
		f->r = ft_rand();
		f->g = ft_rand();
		f->b = ft_rand();
	}
	while (i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			f->y0 = (j - WIDTH / 2) * f->scale;
			f->x0 = (i - HEIGHT / 2) * f->scale;
			f->color = color_generator(f->func(f), f);
			mlx_put_pixel(f->image, i, j, f->color);
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
	f->disco_mode = -1;
	f->a = 255;
	f->scale = 4.0 / WIDTH;
	f->precision = 100;
	f->mlx = mlx_init(WIDTH, HEIGHT, "Fractol", true);
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
	if (k_data.key == MLX_KEY_D && k_data.action == MLX_PRESS)
		f->disco_mode *= -1;
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
	if (argc == 2 && !ft_strcmp(argv[1], "Mandelbrot"))
		f->func = &is_in_mandelbrot;
	else if (argc == 4 && !ft_strcmp(argv[1], "Julia"))
	{
		f->julia_c_real = ft_atold(argv[2]);
		f->julia_c_imaginary = ft_atold(argv[3]);
		f->func = &is_in_julia;
	}
	else if (argc == 2 && !ft_strcmp(argv[1], "Ship"))
		f->func = &is_in_burning_ship;
	else if (argc == 2 && !ft_strcmp(argv[1], "Multibrot3"))
		f->func = &is_in_multibrot3;
	else
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_fractol	f;

	if (!validity_check(&f, argc, argv))
		print_usage();
	initialize_fractol(&f);
	mlx_key_hook(f.mlx, &ft_keyboard_hooks, &f);
	mlx_loop_hook(f.mlx, draw_fractals, &f);
	mlx_loop(f.mlx);
	mlx_terminate(f.mlx);
	return (EXIT_SUCCESS);
}
