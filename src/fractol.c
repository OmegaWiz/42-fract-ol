/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:54:30 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/04/12 08:54:46 by kkaiyawo         ###   ########.fr       */
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
		if (sqrt(pow(k.x, 2) + pow(k.y, 2)) > 2)
			return (i);
		z.x = k.x;
		z.y = k.y;
		i++;
	}
	return (0);
}

void	draw(t_data *img, int (*iter)(t_z, t_z), int *color, t_z dimen, t_z z)
{
	t_z	btml;
	t_z	p;
	t_z	pixel;
	int	ci;

	btml.x = dimen.x / -2;
	btml.y = dimen.y / -2;
	p.x = btml.x;
	while (p.x < dimen.x / 2)
	{
		p.y = btml.y;
		while (p.y < dimen.y / 2)
		{
			ci = iter(p, z);
			pixel.x = ((p.x - btml.x) / dimen.x) * WIN_HEIGHT;
			pixel.y = ((p.y - btml.y) / dimen.y) * WIN_WIDTH;
			if (ci > 0)
				ci = 0x990000;
			else
				ci = 0x000000;
			my_mlx_pixel_put(img, pixel, ci);
			p.y += dimen.y / WIN_WIDTH;
		}
		p.x += dimen.x / WIN_HEIGHT;
	}
}

int	close_esc(int keycode, void *param)
{
	t_vars	*vars;

	vars = (t_vars *) param;
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}
//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);

int	main(int argc, char **argv)
{
	t_data	img;
	t_vars	vars;
	t_z		dimension;
	t_z		m_init;
	int		color[] = {0, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11};

	//init
	(void) argc;
	(void) argv;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "minilibx test");
	img.img = mlx_new_image(vars.mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	//load mandelbrot
	m_init.x = 0;
	m_init.y = 0;
	//set limit for plotting
	dimension.x = 2;
	dimension.y = 2;
	//put color to image
	draw(&img, mandelbrot, color, dimension, m_init);
	//draw on screen
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, close_esc, (void *) &vars);
	mlx_loop(vars.mlx);
	return (0);
}
