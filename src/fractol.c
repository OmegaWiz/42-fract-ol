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

int	mandelbrot(t_z c, t_z z)
{
	int	i;
	t_z	k;

	i = 1;
	while (i < 30)
	{
		k.x = pow(z.x, 2) - pow(z.y, 2) + c.x;
		k.y = (2 * z.x * z.y) + c.y;
		if (pow(k.x, 2) + pow(k.y, 2) > 4)
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
				color = (float) 0xcdd6f4 / color;
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

int	close_esc(int keycode, void* param)
{
	t_vars	*vars;

	vars = (t_vars *) param;
	printf("Pressed: %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
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
	t_z		cen;
	t_z		sz;
	t_vars	*vars;

	vars = (t_vars *) param;
	if (button != 1 && button != 2)
		return (0);
	zoomidx = 1;
	if (button == 1)
		zoomidx = 1.1;
	if (button == 2)
		zoomidx = 0.9;
	printf("Clicked: %d\n", button);
	printf("%f %f|%f,%f|%f\n", zoomidx, vars->mn.x, vars->mx.x, vars->mn.y, vars->mx.y);
	cen.x = (vars->mx.x + vars->mn.x) / 2;
	cen.y = (vars->mx.y + vars->mn.y) / 2;
	sz.x = (vars->mx.x - vars->mn.x) / 2;
	sz.y = (vars->mx.y - vars->mn.y) / 2;
	vars->mx.x = cen.x + (sz.x * zoomidx);
	vars->mx.y = cen.y + (sz.y * zoomidx);
	vars->mn.x = cen.x - (sz.x * zoomidx);
	vars->mn.y = cen.y - (sz.y * zoomidx);
	printf("%f %f|%f|%f|%f,%f|%f|%f|%f\n", zoomidx, vars->mn.x, vars->mx.x, cen.x, sz.x, vars->mn.y, vars->mx.y, cen.y, sz.y);
	draw(vars, mandelbrot);
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
	draw(vars, mandelbrot);
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
	(void) argc;
	(void) argv;
	init(&vars);
	//load mandelbrot
	return (0);
}
