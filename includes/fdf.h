/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:09:56 by malrifai          #+#    #+#             */
/*   Updated: 2024/11/30 17:32:44 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
//# include "../sources/minilibx/mlx.h"
# include <mlx.h>
# include <X11/X.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
#define ESC_KEY 65307

typedef struct s_point
{
	int		z;
	int		x;
	int		y;
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

// void		drawLineH(int x0, int y0, int x1, int y1, t_mlx *mlx);
// void		drawLineV(int x0, int y0, int x1, int y1, t_mlx *mlx);
void		draw_line(int *x, int *y, t_mlx *mlx);
// void		draw_line(int x0, int y0, int x1, int y1, t_mlx *mlx);
void		apply_isometric(t_point *point);
t_point		**get_map(char *file, int *argc, int *rows);

#endif
