/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:15:21 by malrifai          #+#    #+#             */
/*   Updated: 2024/11/23 00:38:44 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void swap(int *x0, int *y0, int *x1, int *y1)
{
  int temp;

  temp = *x0;
  *x0 = *x1;
  *x1 = temp;
  temp = *y0;
  *y0 = *y1;
  *y1 = temp;
}

void drawLineH(int x0, int y0, int x1, int y1, t_mlx *mlx) 
{
    if (x0 > x1)
      swap(&x0, &y0, &x1, &y1);

    int dx = x1 - x0;
    int dy = y1 - y0;
    int dir;
    
    if (dx < 0)
      dir = -1;
    else
      dir = 1;
    dy *= dir;

    if (dx != 0)
    {
        int y = y0;
        int p = 2 * dy - dx;/* condition */

        int i = 0;
        while (i <= dx)
        {
            //putPixel(x0 + i, y);
            mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x0 + i, y, mlx->color);
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

void drawLineV(int x0, int y0, int x1, int y1, t_mlx *mlx) {
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
            mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y0 + i,  mlx->color);
            if (p >= 0)
            {
                x += dir;
                p -= 2 * dy;
            }
            p += 2 * dx;
            i++;
        }
    }
}

/*void test_lines(t_mlx *mlx)
{
    int test_map[][4] = {
        {100, 100, 200, 100}, // Horizontal line
        {100, 100, 100, 200}, // Vertical line
        {100, 100, 200, 200}, // Diagonal line
        {200, 100, 100, 200}  // Reverse diagonal
    };
    int num_lines = 4;

    for (int i = 0; i < num_lines; i++)
    {
        drawLineH(test_map[i][0], test_map[i][1], test_map[i][2], test_map[i][3], mlx);
    }
}

int	main(void)
{
	//void	*mlx_win;
  t_mlx mlx_data;
  
  mlx_data.mlx_ptr = mlx_init();
  mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, 1920, 1080, "Hello world!");
  mlx_data.color = 0xFFFFFF;
  test_lines(&mlx_data);
	mlx_loop(mlx_data.mlx_ptr);
}*/

