/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:19:15 by malrifai          #+#    #+#             */
/*   Updated: 2024/11/23 20:11:27 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>

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
  printf("%d/n", color);
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
  int width = 1920 / cols;
  int len = 1080 / rows;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mlx_data->color = map[i][j].color;
            //printf("%d", mlx_data->color);
            // Draw horizontal line to the next point in the row
            if (j + 1 < cols)
                drawLineH(map[i][j].x * width, map[i][j].y * len,
                          map[i][j + 1].x * width, map[i][j + 1].y * len, mlx_data);

            // Draw vertical line to the next point in the column
            if (i + 1 < rows)
                drawLineV(map[i][j].x * width, map[i][j].y * len,
                          map[i + 1][j].x * width, map[i + 1][j].y * len, mlx_data);
        }
    }
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
  mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, 1920, 1080, "Hello world!");
  mlx_data.color = 0xFFFFFF;
  int fd = open(argv[1], O_RDONLY);
  test_lines(&mlx_data, map, get_row_numbers(fd), argc);
	mlx_loop(mlx_data.mlx_ptr);
}
