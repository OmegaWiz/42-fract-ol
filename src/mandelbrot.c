/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:08:56 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/04/11 15:37:22 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

float	mandelbrot(int it, t_z z, t_z c)
{
	t_z	tmp;

	if (it == 0)
		return (pow(z.x, 2) + pow(z.y, 2));
	tmp.x = pow(z.x, 2) - pow(z.y, 2) + c.x;
	tmp.y = 2 * (z.x + z.y) + c.y;
	return (mandelbrot(it - 1, tmp, c));
}

int	is_mdb(t_z p)
{
	t_z	tmp;

	tmp.x = 0;
	tmp.y = 0;
	if (mandelbrot(10, tmp, p) <= (float) 2)
		return (1);
	return (0);
}
