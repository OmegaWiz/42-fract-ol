/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:54:30 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/04/11 13:02:00 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
x	horizontal	width
y	vertical	height
*/

int	is_circle(t_dim d, float x, float y)
{
	if (pow(x - d.x, 2) + pow(y - d.y, 2) <= pow(d.s, 2))
		return (1);
	return (0);
}

void	draw(t_data *img, int (*isShape)(t_dim, float, float), t_dim d, int color)
{
	int	i;
	int	j;

	i = 1;
	while (i < WIN_WIDTH)
	{
		j = 1;
		while (j < WIN_HEIGHT)
		{
			if (isShape(d, i, j))
			{
				my_mlx_pixel_put(img, i, j, color);
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_dim	d;

	(void) argc;
	(void) argv;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "minilibx test");
	img.img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	//write_square(&img, 100, 100, 100);
	d.x = 500;
	d.y = 500;
	d.s = 250;
	draw(&img, is_circle, d, 0xCDD6F4);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
