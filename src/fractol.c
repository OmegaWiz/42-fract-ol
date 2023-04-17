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
	while (i < 80)
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

void	draw(t_vars *vars, int (*iter)(t_z, t_z))
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
			color = iter(c, vars->mi);
			if (color > 0)
				color = vars->scheme / color;
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
int	close_esc(int keycode, void* param)
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
		draw(vars, julia, vars->colorange[vars->scheme]);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	}
	if (keycode == 45)
	{
		vars->scheme++;
		vars->scheme %= 3;
		draw(vars, mandelbrot, vars->colorange[vars->scheme]);
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
	float	zoomidx;
	t_vars	*vars;
	t_z		mouse;

	vars = (t_vars *) param;
	printf("Clicked: %d\n", button);
	if (button != 4 && button != 5)
		return (0);
	if (button == 4)
		zoomidx = 1.1;
	if (button == 5)
		zoomidx = 0.9;
	mouse.x = vars->mn.x + (float)x / (float)WIN_WIDTH * (vars->mx.x - vars->mn.x);
	mouse.y = vars->mn.y + (float)y / (float)WIN_HEIGHT * (vars->mx.y - vars->mn.y);
	vars->mn.x = mouse.x - (zoomidx * (mouse.x - vars->mn.x));
	vars->mx.x = mouse.x + (zoomidx * (vars->mx.x - mouse.x));
	vars->mn.y = mouse.y - (zoomidx * (mouse.y - vars->mn.y));
	vars->mx.y = mouse.y + (zoomidx * (vars->mx.y - mouse.y));
	draw(vars, mandelbrot, vars->colorange[vars->scheme]);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

int	do_none(void *data)
{
	return (0);
}

void	init(t_vars *vars)
{
	t_data	*d;

	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "fractol");
	d = &(vars->img);
	d->img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	d->addr = mlx_get_data_addr(d->img, &(d->bpp), &(d->line_len), &(d->end));
	vars->mi.x = 0;
	vars->mi.y = 0;
	vars->mx.y = 2;
	vars->mx.x = (vars->mx.y) * (WIN_WIDTH / WIN_HEIGHT);
	vars->mn.x = vars->mx.x * -1;
	vars->mn.y = vars->mx.y * -1;
	vars->scheme = 0;

	draw(vars, mandelbrot, vars->colorange[vars->scheme]);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	mlx_loop_hook(vars->mlx, do_none, (void *) vars);
	mlx_hook(vars->win, 17, 0, close_x, (void *) vars);
	mlx_key_hook(vars->win, close_esc, (void *) vars);
	mlx_mouse_hook(vars->win, zoom, (void *) vars);
	mlx_loop(vars->mlx);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	//init
	if (argc != 2)
	{
		printf("Incorrect number of parameters. Correct format is `./fractol {fractol type}`\n");
		return (0);
	}
	if (strcmp(argv[1], "mandelbrot") == 0)
		init(&vars);
	else if (strcmp(argv[1], "julia") == 0)
	{
		init(&vars);
	}
	else
	{
		printf("Sorry, we currently do not offer said set. The available set is either mandelbrot or julia.\n");
	}
	return (0);
}
