/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:02:41 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/04/11 15:23:23 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H

# define FRACTOL_H

# include <math.h>

# include "../mlx/mlx.h"
# include "../lib/libft/libft.h"

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1000
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 1000
# endif

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_z {
	float	x;
	float	y;
}	t_z;

typedef struct s_dim {
	float	x;
	float	y;
	float	s;
}	t_dim;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
float	mandelbrot(int it, t_z z, t_z c);
int		is_mdb(t_z p);

#endif
