int	old_is_circle(t_dim d, float x, float y)
{
	if (pow(x - d.x, 2) + pow(y - d.y, 2) <= pow(d.s, 2))
		return (1);
	return (0);
}

void	old_draw(t_data *img, int (*isShape)(t_z), int color)
{
	t_z	z;

	z.x = -5;
	while (z.x <= 5)
	{
		z.y = -5;
		while (z.y <= 5)
		{
			if (isShape(z))
			{
				my_mlx_pixel_put(img, (z.x + 5.01) * 100, (z.y + 5.01) * 100, color);
			}
			z.y += 0.01;
		}
		z.x += 0.01;
	}
}


float	old_mandelbrot(int it, t_z z, t_z c)
{
	t_z	tmp;

	if (it == 0)
		return (pow(z.x, 2) + pow(z.y, 2));
	tmp.x = pow(z.x, 2) - pow(z.y, 2) + c.x;
	tmp.y = 2 * (z.x + z.y) + c.y;
	return (mandelbrot(it - 1, tmp, c));
}

int	old_is_mdb(t_z p)
{
	t_z	tmp;

	tmp.x = 0;
	tmp.y = 0;
	if (mandelbrot(10, tmp, p) <= (float) 2)
		return (1);
	return (0);
}
