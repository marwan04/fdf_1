/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:19:15 by malrifai          #+#    #+#             */
/*   Updated: 2024/11/26 01:15:04 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>
#include <math.h>

int get_color(char *cell)
{
  int color;
  char **splited_cell;

  color = 0xFFFFFF;
  if(ft_strchr(cell, ','))
  {
    splited_cell = ft_split(cell, ',');
    //printf("%s\n",splited_cell[1]);
    color = ft_atoi_base(splited_cell[1], "0123456789ABCDEF");
    if (color == 0)
      color = 0xFFFFFF;
  }
  //printf("%d/n", color);
  return (color);
}

t_point	*split_row(char *row, int y, int *argc)
{
	char	**splited_row;
	t_point *points;
	int		x;

	x = 0;
	splited_row = ft_split(row, ' ');
	while (splited_row[*argc])
		*argc = *argc + 1;
	points = (t_point *)malloc(*argc * sizeof(t_point));
	while (x < *argc)
	{
    points[x].x = x;
    points[x].y = y;
		points[x].z = ft_atoi(splited_row[x]);
    points[x].color = get_color(splited_row[x]);
		free(splited_row[x]);
		x++;
	}
	free(splited_row);
	return (points);
}

int	get_row_numbers(int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

t_point **get_map(char *file, int *argc)
{
     int   fd;
     int   count;
     char  *line;
     t_point   **map;
     int   y;

     y = 0;
     fd = open(file, O_RDONLY);
     count = get_row_numbers(fd);
     map = malloc(count * sizeof(t_point *));
     fd = open(file, O_RDONLY);
     line = get_next_line(fd);
     while (line != NULL)
     {
       map[y] = split_row(line, y, argc);
       y++;
       free(line);
       line = get_next_line(fd);
     }
     close(fd);
     return (map);
}

/*void	print_int_array(t_point **array, int rows, int cols)
{
	if (!array)
	{
		printf("Array is NULL.\n");
		return ;
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%d\t", array[i][j].z);
		}
		free(array[i]);
		printf("\n");
	}

  for (int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
      printf("x:%d  y:%d\t",array[i][j].x, array[i][j].y);
    }
    printf("\n");
  }
	free(array);
}*/

void test_lines(t_mlx *mlx_data, t_point **map, int rows, int cols)
{
//  int width = 1920 / cols;
//  int len = 1080 / rows;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mlx_data->color = map[i][j].color;
            //printf("%d", mlx_data->color);
            // Draw horizontal line to the next point in the row
            if (j + 1 < cols)
                drawLineH(map[i][j].x, map[i][j].y,
                          map[i][j + 1].x, map[i][j + 1].y, mlx_data);

            // Draw vertical line to the next point in the column
            if (i + 1 < rows)
                drawLineV(map[i][j].x , map[i][j].y,
                          map[i + 1][j].x, map[i + 1][j].y, mlx_data);
        }
    }
}

void apply_isometric(t_point *point, double cos_angle, double sin_angle) {
    int previous_x = point->x;
    int previous_y = point->y;

    point->x = (previous_x - previous_y) * cos_angle;
    point->y = (previous_x + previous_y) * sin_angle - point->z;

   point->x += 960; // Adjusted center
point->y += 540; // Adjusted center

printf("Transformed Point: x=%d, y=%d\n", point->x, point->y);
}

int	main(int argc, char **argv)
{
  argc = 0;
  t_point **map = get_map(argv[1], &argc);
  //print_int_array(map, 11, argc);
//	print_int_array(map, 11, argc);
	//void	*mlx_win;
  t_mlx mlx_data;

  mlx_data.mlx_ptr = mlx_init();
  mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, 1920, 1080, "FDF");
  mlx_data.img_ptr = mlx_new_image(mlx_data.mlx_ptr, 1920, 1080);
mlx_data.img_data = mlx_get_data_addr(mlx_data.img_ptr, &mlx_data.bpp,
                                      &mlx_data.line_length, &mlx_data.endian);

  mlx_data.color = 0xFFFFFF;
  int fd = open(argv[1], O_RDONLY);
  int cols = get_row_numbers(fd);
  close(fd);
double angle = 30.0;  
    double cos_angle = cos(angle * M_PI / 180.0);
    double sin_angle = sin(angle * M_PI / 180.0);

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < argc; j++) {
            apply_isometric(&map[i][j], cos_angle, sin_angle);
        }
    }
test_lines(&mlx_data, map, cols, argc);

  mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, mlx_data.img_ptr, 0, 0);
	mlx_loop(mlx_data.mlx_ptr);
}
