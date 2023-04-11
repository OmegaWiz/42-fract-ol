/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:08:56 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/04/11 15:16:26 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

float	mandelbrot(int it, p_z z, p_z c)
{
	p_z	tmp;

	if (it == 0)
		return (pow(z.x, 2) + pow(z.y, 2));
	tmp.x = pow(z.x, 2) - pow(z.y, 2) + c.x;
	tmp.y = 2 * (z.x + z.y) + c.y;
	return (mandelbrot(it - 1, tmp, c));
}

int	is_mdb(p_z p)
{
	if (mandelbrot(10, 0, p) <= 2.0)
		return (1);
	return (0);
}
