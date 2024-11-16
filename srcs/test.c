/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:16:50 by malrifai          #+#    #+#             */
/*   Updated: 2024/11/16 16:42:24 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

int	main(void)
{
	void	*mlx;
	//void	*mlx_win;

	mlx = mlx_init();
	mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
}
