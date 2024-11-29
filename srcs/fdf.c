/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:19:15 by malrifai          #+#    #+#             */
/*   Updated: 2024/11/29 19:14:27 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>
#include <stdio.h>

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
			printf("Drawing Line: Start(%d, %d) -> End(%d, %d)\n", map[i][j].x,
				map[i][j].y, map[i][j + 1].x, map[i][j + 1].y);
			if (j + 1 < cols)
				drawLineH(map[i][j].x, map[i][j].y, map[i][j + 1].x, map[i][j
					+ 1].y, mlx_data);
			if (i + 1 < rows)
				drawLineV(map[i][j].x, map[i][j].y, map[i + 1][j].x, map[i
					+ 1][j].y, mlx_data);
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
		int rows;
		int i;
		int j;
	t_point	**map;
		t_mlx mlx_data;

	if (argc == 2)
	{
		map = get_map(argv[1], &argc, &rows);
		i = 0;
		j = 0;
		mlx_data.mlx_ptr = mlx_init();
		mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, 1920, 1080, "FDF");
		mlx_data.img_ptr = mlx_new_image(mlx_data.mlx_ptr, 1920, 1080);
		mlx_data.img_data = mlx_get_data_addr(mlx_data.img_ptr, &mlx_data.bpp,
				&mlx_data.line_length, &mlx_data.endian);
		while (i < rows)
		{
			j = 0;
			while (j < argc)
				apply_isometric(&map[i][j++]);
			i++;
		}
		// ft_printf("Original Point: x=%d, y=%d, z=%d\n", map[i][j].x, map[i][j].y, map[i][j].z);
		test_lines(&mlx_data, map, rows, argc);
		mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr,
			mlx_data.img_ptr, 0, 0);
		mlx_loop(mlx_data.mlx_ptr);
	}
}
