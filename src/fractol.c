/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:54:30 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/04/07 15:54:25 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx/mlx.h"

int	main(int argc, char **argv)
{
	void	*mlx_ptr;

	(void) argc;
	(void) argv;
	mlx_ptr = mlx_init();
	mlx_new_window(mlx_ptr, 1920, 1080, "MiniLibX - Test");
	mlx_loop(mlx_ptr);
	return (0);
}