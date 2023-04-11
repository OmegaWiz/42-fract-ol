/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:54:30 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/04/11 09:03:24 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	write_square(t_data *img, int x, int y, int n)
{
	int	i;

	i = 0;
	while (i <= n)
	{
		my_mlx_pixel_put(img, x + i, y, 0x00FFFFFF);
		i++;
	}
	i = 0;
	while (i <= n)
	{
		my_mlx_pixel_put(img, x + i, y + n, 0x00FFFFFF);
		i++;
	}
	i = 0;
	while (i <= n)
	{
		my_mlx_pixel_put(img, x, y + i, 0x00FFFFFF);
		i++;
	}
	i = 0;
	while (i <= n)
	{
		my_mlx_pixel_put(img, x + n, y + i, 0x00FFFFFF);
		i++;
	}
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	(void) argc;
	(void) argv;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "minilibx test");
	img.img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	write_square(&img, 100, 100, 100);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
