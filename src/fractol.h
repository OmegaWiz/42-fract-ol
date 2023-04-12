/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:02:41 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/04/12 09:33:30 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H

# define FRACTOL_H

# include <math.h>

# include<stdio.h>

# include "../mlx/mlx.h"
# include "../lib/libft/libft.h"

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1920
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 1080
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

#endif
