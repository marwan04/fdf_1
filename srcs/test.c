/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:16:50 by malrifai          #+#    #+#             */
/*   Updated: 2024/11/18 20:50:54 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <X11/X.h>
#include <math.h>
// Define the rotation angles for isometric projection
#define ISO_ANGLE_X (M_PI / 6) // 30 degrees
#define ISO_ANGLE_Y (M_PI / 6) // 30 degrees
#define WIDTH 800
#define HEIGHT 800
typedef struct s_point
{
    double x;
    double y;
    double z;
} t_point;
t_point rotate_isometric(t_point p)
{
    t_point result;
    // Rotate around X-axis
    result.x = p.x;
    result.y = p.y * cos(-ISO_ANGLE_X) + p.z * sin(-ISO_ANGLE_X);
    result.z = p.y * sin(-ISO_ANGLE_X) + p.z * cos(-ISO_ANGLE_X);
    // Rotate around Y-axis
    double temp_x = result.x * cos(-ISO_ANGLE_Y) - result.z * sin(-ISO_ANGLE_Y);
    result.z = result.x * sin(-ISO_ANGLE_Y) + result.z * cos(-ISO_ANGLE_Y);
    result.x = temp_x;
    return result;
}
typedef struct s_f
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
    int     shift;
}           t_f;
int mouse_hook(int button, int x, int y, t_f *p)
{
    if (button == 1)
        p->shift += 1;
    printf("Button: %d, x: %d, y: %d\n", button, x, y);
    return (0);
}
// int put_grid(t_f *p)
// {
//     int     x;
//     int     y;
//     t_point point;
//     t_point iso_point;
//     int     screen_x;
//     int     screen_y;
//     y = 0;
//     while (y <= 300) // Grid height
//     {
//         x = 0;
//         while (x <= 400) // Grid width
//         {
//                         if (x % 10 == 0 || y % 10 == 0)
//             {
//             // Set the 3D grid point (z can be used for height variations, set to 0 for flat grid)
//             point.x = x;
//             point.y = y;
//             point.z = 0;
//             // Apply isometric transformation
//             iso_point = rotate_isometric(point);
//             // Map isometric coordinates to screen space
//             screen_x = (int)(iso_point.x + 100); // Center X on the screen
//             screen_y = (int)(iso_point.y + 200); // Center Y on the screen
//             // Draw grid point
//             if (screen_x >= 0 && screen_x < WIDTH && screen_y >= 0 && screen_y < HEIGHT)
//                 *(unsigned int *)(p->addr + (4 * screen_x + p->line_len * screen_y)) = 0xFF0000;
//             }
//             x++; // Adjust grid spacing
//         }
//         y++; // Adjust grid spacing
//     }
//     // Render the grid
//     mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
//     return (0);
// }
// int  put_grid(t_f *p)
// {
//  int x;
//  int y;
//  int i;
//  y = 100;
//  while (y <= 400)
//  {
//      x = 100;
//      while (x <= 700)
//      {
//          if (x % 10 == 0 || y % 10 == 0)
//          {
//              *(unsigned int *)(p->addr + (4 * x + p->line_len * y)) = 0xFF0000;
//          }
//          else
//              *(unsigned int *)(p->addr + (4 * x + p->line_len * y)) = 0x0;
//          x++;
//      }
//      y++;
//  }
//  mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
//  return (0);
// }

int draw_line(t_f *p)
{
    int x = 100;    
    int y = 500;    
    double slope = tan(M_PI / 6);

    while (x <= 400) 
    {
        int y_int = y - slope * (x - 100);
        *(unsigned int *)(p->addr + (4 * x + p->line_len * y_int)) = 0xFF0000;
        x++; 
    } 

    while (x >= 100) 
    {
           int y_int = y + slope * (x - 100);
           *(unsigned int *)(p->addr + (4 * x + p->line_len * y_int)) = 0xFF0000;
           x--; 
    }
    x = 400;
    y = 500;
    while (x <= 700)
    {
          int y_int = y - slope * (x - 100);
          *(unsigned int *)(p->addr + (4 * x + p->line_len * y_int)) = 0xFF0000;
         x++;
    } 


    mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0); // Display the image
    return (0);
}

int main(void)
{
    t_f p;
    p.shift = 1;
    p.mlx = mlx_init();
    p.win = mlx_new_window(p.mlx, 800, 800, "fdf");
    p.img = mlx_new_image(p.mlx, 800, 800);
    p.addr = mlx_get_data_addr(p.img, &p.bpp, &p.line_len, &p.endian);
    mlx_hook(p.win, ButtonPress, ButtonPressMask, mouse_hook, &p);
    mlx_loop_hook(p.mlx, draw_line, &p);
    mlx_loop(p.mlx);
    return (0);
}
