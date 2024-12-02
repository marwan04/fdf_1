/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <malrifai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:15:21 by malrifai          #+#    #+#             */
/*   Updated: 2024/12/02 21:43:00 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	set_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= 1920 || y >= 1080)
		return ;
	pixel = mlx->img_data + (y * mlx->line_length + x * (mlx->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	draw_line_loop(int *start, int *end, t_mlx *mlx, t_draw draw_data)
{
	int	e2;

	while (1)
	{
		set_pixel(mlx, start[0], start[1], mlx->color);
		if (start[0] == end[0] && start[1] == end[1])
			break ;
		e2 = 2 * draw_data.err;
		if (e2 > -draw_data.dy)
		{
			draw_data.err -= draw_data.dy;
			start[0] += draw_data.sx;
		}
		if (e2 < draw_data.dx)
		{
			draw_data.err += draw_data.dx;
			start[1] += draw_data.sy;
		}
	}
}

void	draw_line(int *start, int *end, t_mlx *mlx)
{
	t_draw	draw_data;

	draw_data.dx = abs(end[0] - start[0]);
	draw_data.dy = abs(end[1] - start[1]);
	draw_data.err = draw_data.dx - draw_data.dy;
	if (start[0] < end[0])
		draw_data.sx = 1;
	else
		draw_data.sx = -1;
	if (start[1] < end[1])
		draw_data.sy = 1;
	else
		draw_data.sy = -1;
	draw_line_loop(start, end, mlx, draw_data);
}

void	test_lines(t_mlx *mlx_data, t_point **map, int rows, int cols)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			mlx_data->color = map[i][j].color;
			if (j + 1 < cols)
				draw_line((int []){map[i][j].x, map[i][j].y},
					(int []){map[i][j + 1].x, map[i][j + 1].y}, mlx_data);
			if (i + 1 < rows)
				draw_line((int []){map[i][j].x, map[i][j].y},
					(int []){map[i + 1][j].x, map[i + 1][j].y}, mlx_data);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window((*mlx_data).mlx_ptr, (*mlx_data).win_ptr,
		(*mlx_data).img_ptr, 0, 0);
}
