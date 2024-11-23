/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:09:56 by malrifai          #+#    #+#             */
/*   Updated: 2024/11/23 12:10:43 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include "../sources/minilibx/mlx.h"

typedef struct s_point
{
	int	z;
	int	x;
	int	y;
  int color;
}		t_point;

typedef struct s_mlx
{
      void *mlx_ptr;
      void *win_ptr;
      int color;
} t_mlx;

void drawLineH(int x0, int y0, int x1, int y1, t_mlx *mlx);
void drawLineV(int x0, int y0, int x1, int y1, t_mlx *mlx);


#endif
