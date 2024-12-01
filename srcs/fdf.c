/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <malrifai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:19:15 by malrifai          #+#    #+#             */
/*   Updated: 2024/12/01 21:48:36 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	free_map(t_point **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(map[i++]);
	free(map);
}

int	handle_keypress(int keycode, t_mlx *mlx_data)
{
	if (keycode == ESC_KEY)
	{
		free_map(mlx_data->map, mlx_data->rows);
		mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->img_ptr);
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
		mlx_destroy_display(mlx_data->mlx_ptr);
		free(mlx_data->mlx_ptr);
		exit(0);
	}
	return (0);
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
			printf("Drawing Line: Start(%d, %d) -> End(%d, %d)\n", map[i][j].x,
				map[i][j].y, map[i][j + 1].x, map[i][j + 1].y);
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
}

// ft_printf("Original Point: x=%d, y=%d, z=%d\n", map[i][j].x,
// map[i][j].y, map[i][j].z);
void	init_window(t_mlx *mlx_data, t_point **map, int rows)
{
	(*mlx_data).mlx_ptr = mlx_init();
	(*mlx_data).win_ptr = mlx_new_window((*mlx_data).mlx_ptr, 1920, 1080,
			"FDF");
	(*mlx_data).img_ptr = mlx_new_image((*mlx_data).mlx_ptr, 1920, 1080);
	(*mlx_data).img_data = mlx_get_data_addr((*mlx_data).img_ptr,
			&(*mlx_data).bpp, &(*mlx_data).line_length, &(*mlx_data).endian);
	(*mlx_data).map = map;
	(*mlx_data).rows = rows;
}

int	main(int argc, char **argv)
{
	int		rows;
	int		i;
	int		j;
	t_point	**map;
	t_mlx	mlx_data;

	if (argc == 2)
	{
	 	map = get_map(argv[1], &argc, &rows);
		i = 0;
		j = 0;
	 	init_window(&mlx_data, map, rows);
		while (i < rows)
		{
			j = 0;
			while (j < argc)
				apply_isometric(&map[i][j++]);
			i++;
		}
		test_lines(&mlx_data, map, rows, argc);
		mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr,
			mlx_data.img_ptr, 0, 0);
		mlx_key_hook(mlx_data.win_ptr, handle_keypress, &mlx_data);
		mlx_hook(mlx_data.win_ptr, 2, 1L << 0, handle_keypress, &mlx_data);
		mlx_loop(mlx_data.mlx_ptr);
	}
}