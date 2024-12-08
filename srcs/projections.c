/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <malrifai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:26:15 by malrifai          #+#    #+#             */
/*   Updated: 2024/12/08 20:42:27 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	apply_isometric(t_point *point)
{
	double	angle;
	double	cos_angle;
	double	sin_angle;

	angle = 30.0;
	cos_angle = cos(angle * M_PI / 180.0);
	sin_angle = sin(angle * M_PI / 180.0);
	point->x = (point->original_x - point->original_y) * cos_angle;
	point->y = (point->original_x + point->original_y) * sin_angle - point->z;
	point->x += 600;
	point->y -= 240;
}

void	apply_isometric_to_map(t_point **map, int rows, int cols)
{
	int	y;
	int	x;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			apply_isometric(&map[y][x]);
			x++;
		}
		y++;
	}
}

void	disable_isometric(t_point *point)
{
	point->x = point->original_x;
	point->y = point->original_y;
	point->z = point->original_z;
}

void	disable_isometric_to_map(t_point **map, int rows, int cols)
{
	int	y;
	int	x;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			disable_isometric(&map[y][x]); // Reset each point
			x++;
		}
		y++;
	}
}

