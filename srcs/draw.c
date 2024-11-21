/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:15:21 by malrifai          #+#    #+#             */
/*   Updated: 2024/11/21 21:30:21 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

void swap(int *x0, int *y0, int *x1, int *y1)
{
  int temp;

  temp = *x0;
  *x0 = *x1;
  *x1 = temp;
  temp = *y0;
  *y0 = y1;
  *y1 = temp;
}

void drawLineH(int x0, int y0, int x1, int y1) 
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
        int p = 2 * dy - dx;

        int i = 0;
        while (i <= dx)
        {
            putPixel(x0 + i, y);
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

void drawLineV(int x0, int y0, int x1, int y1) {
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
            putPixel(x, y0 + i);
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

int	main(void)
{
	void	*mlx;
	//void	*mlx_win;

	mlx = mlx_init();
	mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
}

