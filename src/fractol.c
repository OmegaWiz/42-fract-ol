/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:54:30 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/04/12 10:38:35 by kkaiyawo         ###   ########.fr       */
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
		if (sqrt(pow(k.x, 2) + pow(k.y, 2)) > 2)
			return (i);
		z.x = k.x;
		z.y = k.y;
		i++;
	}
	return (0);
}

void	draw(t_data *img, int (*iter)(t_z, t_z), t_z mn, t_z mx, t_z z)
{
	t_z		p;
	t_z		c;
	int		color;

	p.x = 0;
	while (p.x < WIN_WIDTH)
	{
		p.y = 0;
		c.x = ((p.x / WIN_WIDTH) * (mx.x - mn.x)) + mn.x;
		while (p.y < WIN_HEIGHT)
		{
			c.y = (((WIN_HEIGHT - p.y) / WIN_HEIGHT) * (mx.y - mn.y)) + mn.y;
			color = iter(c, z);
			if (color > 0)
				color = (float) 0xFFFFFF / color;
			my_mlx_pixel_put(img, p, color);
			p.y++;
		}
		p.x++;
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
	t_z		mx;
	t_z		m_init;
	t_z		mn;

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
	mx.x = 8;
	mx.y = 4.5;
	mn.x = -8;
	mn.y = -4.5;
	//put color to image
	draw(&img, mandelbrot, mn, mx, m_init);
	//draw on screen
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, close_esc, (void *) &vars);
	mlx_loop(vars.mlx);
	return (0);
}
