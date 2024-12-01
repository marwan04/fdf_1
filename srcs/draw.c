/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <malrifai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:15:21 by malrifai          #+#    #+#             */
/*   Updated: 2024/12/01 21:46:41 by malrifai         ###   ########.fr       */
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

/*void swap(int *x0, int *y0, int *x1, int *y1)
{
  int temp;
	t_draw	draw_data;
	int		e2;
	t_draw	draw_data;
	int		e2;

  temp = *x0;
  *x0 = *x1;
  *x1 = temp;
  temp = *y0;
  *y0 = *y1;
  *y1 = temp;
}*/
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

/*void drawLineH(int x0, int y0, int x1, int , t_mlx *mlx)
{
	int	dx;
	int	dy;
	int	dir;
	int	y;
	int	p;
	int	i;

	if (x0 > x1)
		swap(&x0, &y0, &x1, &y1);
	dx = x1 - x0;
	dy = y1 - y0;
	if (dx < 0)
		dir = -1;
	else
		dir = 1;
	dy *= dir;
	if (dx != 0)
	{
		y = y0;
		p = 2 * dy - dx;
		i = 0;
		while (i <= dx)
		{
			set_pixel(mlx, x0 + i, y, mlx->color);
			if (p >= 0)
			{
				y += dir;
				p -= 2 * dx;
			}
			p += 2 * dy;
			i++;
		}
	}
}

void	drawLineV(int x0, int y0, int x1, int y1, t_mlx *mlx) {
	if (y0 > y1)
		swap(&x0, &x1, &y0, &y1);

	int dx = x1 - x0;
	int dy = y1 - y0;
	int dir;
	if (dx < 0)
		dir = -1;
	else
		dir = 1;
	dx *= dir;

	if (dy != 0)
	{
		int x = x0;
		int p = 2 * dx - dy;

		int i = 0;
		while (i <= dy)
		{
			//putPixel(x, y0 + i);
			set_pixel(mlx, x, y0 + i, mlx->color);
			if (p >= 0)
			{
				x += dir;
				p -= 2 * dy;
			}
			p += 2 * dx;
			i++;
		}
	}
}*/
/*void test_lines(t_mlx *mlx)
{
	int	num_lines;

	int test_map[][4] = {
		{100, 100, 200, 100}, // Horizontal line
		{100, 100, 100, 200}, // Vertical line
		{100, 100, 200, 200}, // Diagonal line
		{200, 100, 100, 200}  // Reverse diagonal
	};
	num_lines = 4;
	for (int i = 0; i < num_lines; i++)
	{
		drawLineH(test_map[i][0], test_map[i][1], test_map[i][2],
			test_map[i][3], mlx);
	}
}

int	main(void)
{
	//void	*mlx_win;
  t_mlx mlx_data;

  mlx_data.mlx_ptr = mlx_init();
  mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, 1920, 1080,
		"Hello world!");
  mlx_data.color = 0xFFFFFF;
  test_lines(&mlx_data);
	mlx_loop(mlx_data.mlx_ptr);
}*/
