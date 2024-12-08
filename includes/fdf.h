/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <malrifai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:09:56 by malrifai          #+#    #+#             */
/*   Updated: 2024/12/08 20:37:05 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include <X11/X.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# define ESC_KEY 65307
#define KEY_ISOMETRIC 50
#define KEY_CARTESIAN 51
#define CLEAR 53

typedef struct s_point
{
	int		z;
	int		x;
	int		y;
	int	original_x;
	int	original_y;
	int	original_z;
	int		color;
}			t_point;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		line_length;
	int		endian;
	int		color;
	t_point	**map;
	int		rows;
	int		cols;
}			t_mlx;

typedef struct s_draw
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;

}			t_draw;

typedef struct s_var
{
	int		horizontal_offset;
	int		vertical_offset;
	double	scale_factor;
}			t_var;

void		print_lines(t_mlx *mlx_data, t_point **map, int rows, int cols);
void		apply_isometric_to_map(t_point **map, int rows, int cols);
void		disable_isometric_to_map(t_point **map, int rows, int cols);
t_point		**get_map(char *file, int *argc, int *rows);

#endif
