/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:12:55 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/30 18:59:13 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d			cub3d;

	if (argc != 2)
		return (1);
	cub3d.config = ft_configuration(argv[1]);
	if (!cub3d.config)
		return (1);
	cub3d.mlx = mlx_init();
	cub3d.win = mlx_new_window(cub3d.mlx, SCREEN_WIDTH + 5, SCREEN_HEIGTH + 5, "Cub3D");
	cub3d.img.mlx = mlx_new_image(cub3d.mlx, SCREEN_WIDTH, SCREEN_HEIGTH);
	cub3d.img.addr = mlx_get_data_addr(cub3d.img.mlx, &cub3d.img.bpp, &cub3d.img.line_len, &cub3d.img.endian);
	mlx_loop_hook(cub3d.mlx, &ft_render_game, &cub3d);
	mlx_loop(cub3d.mlx);
	return (0);
}