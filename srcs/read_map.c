/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <malrifai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 19:07:47 by malrifai          #+#    #+#             */
/*   Updated: 2024/12/08 20:44:23 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_color(char *cell)
{
	int		color;
	char	**splited_cell;

	color = 0xFFFFFF;
	splited_cell = ft_split(cell, ',');
	if (!splited_cell)
		return (0);
	if (splited_cell[1] != NULL)
	{
		color = ft_atoi_base(splited_cell[1], 16);
		free(splited_cell[1]);
	}
	free(splited_cell[0]);
	return (free(splited_cell), color);
}

t_point	*split_row(char *row, int y, int *argc, int cols)
{
	char	**splited_row;
	t_point	*points;
	int		x;
	t_var	var;

	x = 0;
	splited_row = ft_split(row, ' ');
	if (!splited_row)
		return (NULL);
	while (splited_row[*argc])
		*argc = *argc + 1;
	var.scale_factor = fmin(1920 / (*argc), 1080 / cols) * 0.7;
	var.horizontal_offset = (1920 - (*argc - 1) * var.scale_factor) / 2;
	var.vertical_offset = (1080 - (cols - 1) * var.scale_factor) / 2;
	points = (t_point *)malloc(*argc * sizeof(t_point));
	while (x < *argc)
	{
		points[x].x = x * var.scale_factor + var.horizontal_offset;
		points[x].y = y * var.scale_factor + var.vertical_offset;
		points[x].z = ft_atoi(splited_row[x]);//* var.scale_factor;
		points[x].original_x = points[x].x;
		points[x].original_y = points[x].y;
		points[x].original_z = points[x].z;
		points[x].color = get_color(splited_row[x]);
		free(splited_row[x]);
		x++;
	}
	return (free(splited_row), points);
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

t_point	**get_map(char *file, int *argc, int *rows)
{
	int		fd;
	char	*line;
	t_point	**map;
	int		y;

	y = 0;
	fd = open(file, O_RDONLY);
	*rows = get_row_numbers(fd);
	map = malloc(*rows * sizeof(t_point *));
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		line = ft_strtrim(line, "\n");
		map[y] = split_row(line, y, argc, *rows);
		y++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}


