/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:54:30 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/04/12 17:40:45by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
x	horizontal	row		height
y	vertical	column	width
*/

void	my_mlx_pixel_put(t_data *data, t_z px, int color)
{
	char	*dst;
	int		x;
	int		y;

	y = (int) px.y;
	x = (int) px.x;
	if (x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	julia(t_z c, t_z z)
{
	int	i;
	t_z	k;
	t_z	l;

	i = 1;
	k.x = c.x;
	k.y = c.y;
	while (i < 80)
	{
		l.x = (k.x * k.x) - (k.y * k.y) + z.x;
		l.y = (2 * k.x * k.y) + z.y;
		k.x = l.x;
		k.y = l.y;
		if ((k.x * k.x) + (k.y * k.y) > 4)
			return (i);
		i++;
	}
	return (0);
}

int	cursed_julia(t_z c, t_z z)
{
	int	i;
	t_z	k;

	i = 1;
	k.x = c.x;
	k.y = c.y;
	while (i < 80)
	{
		k.x = (k.x * k.x) - (k.y * k.y) + z.x;
		k.y = (2 * k.x * k.y) + z.y;
		if ((k.x * k.x) + (k.y * k.y) > 4)
			return (i);
		i++;
	}
	return (0);
}

int	burn(t_z c, t_z z)
{
	int	i;
	t_z	k;

	i = 1;
	while (i < 80)
	{
		k.x = (z.x * z.x) - (z.y * z.y) + c.x;
		k.y = -fabs(2 * z.x * z.y) + c.y;
		if ((k.x * k.x) + (k.y * k.y) > 4)
			return (i);
		z.x = k.x;
		z.y = k.y;
		i++;
	}
	return (0);
}

int	mandelbrot(t_z c, t_z z)
{
	int	i;
	t_z	k;

	i = 1;
	while (i < MAX_ITER)
	{
		k.x = (z.x * z.x) - (z.y * z.y) + c.x;
		k.y = (2 * z.x * z.y) + c.y;
		if ((k.x * k.x) + (k.y * k.y) > 4)
			return (i);
		z.x = k.x;
		z.y = k.y;
		i++;
	}
	return (0);
}

void	draw(t_vars *vars)
{
	t_z		p;
	t_z		c;
	int		color;

	p.x = 0;
	while (p.x < WIN_WIDTH)
	{
		p.y = 0;
		c.x = ((p.x / WIN_WIDTH) * (vars->mx.x - vars->mn.x)) + vars->mn.x;
		while (p.y < WIN_HEIGHT)
		{
			c.y = (WIN_HEIGHT - p.y) / WIN_HEIGHT;
			c.y *= (vars->mx.y - vars->mn.y);
			c.y += vars->mn.y;
			color = vars->iter(c, vars->mi);
			if (color > 0)
				color = vars->scheme[vars->color] * color / MAX_ITER;
			my_mlx_pixel_put(&(vars->img), p, color);
			p.y++;
		}
		p.x++;
	}
}

int	close_x(void* param)
{
	t_vars	*vars;

	vars = (t_vars *) param;
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

/*
123-126
lrud
*/
int	keyb(int keycode, void* param)
{
	t_vars	*vars;
	t_z		sz;
	float	mult;

	vars = (t_vars *) param;
	printf("Pressed: %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (122 < keycode && keycode < 127)
	{
		sz.x = vars->mx.x - vars->mn.x;
		sz.y = vars->mx.y - vars->mn.y;
		mult = 0.1;
		if (keycode % 2)
			mult = -0.1;
		if (keycode < 125)
		{
			vars->mn.x += sz.x * mult;
			vars->mx.x += sz.x * mult;
		}
		else
		{
			vars->mn.y += sz.y * mult;
			vars->mx.y += sz.y * mult;
		}
		draw(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	}
	if (keycode == 45)
	{
		vars->color = (vars->color + 1) % 6;
		printf("%d %x\n", vars->color, vars->scheme[vars->color]);
		draw(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	}
	return (0);
}

/*
4 - scroll up
5 - scroll down
*/
int	zoom(int button, int x, int y, void* param)
{
	t_vars	*vars;
	t_z		mouse;

	vars = (t_vars *) param;
	printf("Clicked: %d\n", button);
	if (button != 4 && button != 5)
		return (0);
	if (button == 4)
		vars->zoomidx = 1.08;
	if (button == 5)
		vars->zoomidx = 1 / 1.08;
	mouse.x = vars->mn.x + ((x / (float)WIN_WIDTH) * (vars->mx.x - vars->mn.x));
	mouse.y = vars->mn.y + ((WIN_HEIGHT - y) / (float)WIN_HEIGHT) * (vars->mx.y - vars->mn.y);
	vars->mn.x = mouse.x - (vars->zoomidx * (mouse.x - vars->mn.x));
	vars->mx.x = mouse.x + (vars->zoomidx * (vars->mx.x - mouse.x));
	vars->mn.y = mouse.y - (vars->zoomidx * (mouse.y - vars->mn.y));
	vars->mx.y = mouse.y + (vars->zoomidx * (vars->mx.y - mouse.y));
	draw(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

int	do_none(void *data)
{
	return (0);
}

void	init(t_vars *vars, int (*iter)(t_z, t_z), t_z mi)
{
	t_data	*d;

	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "fractol");
	d = &(vars->img);
	d->img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	d->addr = mlx_get_data_addr(d->img, &(d->bpp), &(d->line_len), &(d->end));
	vars->mi.x = mi.x;
	vars->mi.y = mi.y;
	vars->mx.y = MAX_INIT;
	vars->mx.x = MAX_INIT * (WIN_WIDTH / WIN_HEIGHT);
	vars->mn.x = vars->mx.x * -1;
	vars->mn.y = vars->mx.y * -1;
	vars->scheme = (int [6]){0xcdd6f4, 0xcad3f5, 0xc6d0f5, 0xff0000, 0x00ff00, 0x0000ff};
	vars->color = 0;
	vars->iter = iter;
	vars->zoomidx = 1;
	draw(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	mlx_loop_hook(vars->mlx, do_none, (void *) vars);
	mlx_hook(vars->win, 17, 0, close_x, (void *) vars);
	mlx_key_hook(vars->win, keyb, (void *) vars);
	mlx_mouse_hook(vars->win, zoom, (void *) vars);
	mlx_loop(vars->mlx);
}

void	print_man(void)
{
	ft_putstr_fd("\033[96mUsage:\033[32m\n", 1);
	ft_putstr_fd("> ./fractol <fractal:uint> <*re:int> <*im:int>\033[0m\n", 1);
	ft_putstr_fd("	fractal: fractol type (0 = Mandelbrot, 1 = Burning ship, 2 = Julia, 3 = Broken Julia)\n", 1);
	ft_putstr_fd("	re(al): real coordinate for julia set (*1000) [-2000, 2000]\n", 1);
	ft_putstr_fd("	im(aginary): imaginary coordinate for julia set (*1000) [-2000, 2000]\n\n", 1);
	ft_putstr_fd("\033[96mKey bindings:\033[0m\n", 1);
	ft_putstr_fd("	[Arrow keys]: Pans the camera\n", 1);
	ft_putstr_fd("	[Scrollwheel]: Zooms in and out\n", 1);
	ft_putstr_fd("	[N]: Change color scheme\n", 1);
	ft_putstr_fd("	[Esc]: Exit application.\n\n\033[93m", 1);
	ft_putstr_fd("\033[0m\n", 1);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_z		mi;

	if (argc == 2)
	{
		mi.x = 0;
		mi.y = 0;
		if (strcmp(argv[1], "0") == 0)
			init(&vars, mandelbrot, mi);
		else if (strcmp(argv[1], "1") == 0)
			init(&vars, burn, mi);
		else
			print_man();
	}
	if (argc == 4)
	{
		mi.x = (float) atoi(argv[2]) / 1000.0;
		mi.y = (float) atoi(argv[3]) / 1000.0;
		printf("%f %f\n", mi.x, mi.y);
		if (-2 > mi.x || -2 > mi.y || 2 < mi.x || 2 < mi.y)
			print_man();
		if (strcmp(argv[1], "2") == 0)
			init(&vars, julia, mi);
		else if (strcmp(argv[1], "3") == 0)
			init(&vars, cursed_julia, mi);
		else
			print_man();
	}
	if (argc != 2)
		print_man();
	return (0);
}
