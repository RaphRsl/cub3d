/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:12:55 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/01 15:15:32 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void	init_cam_settings(t_cub3d *cub3d)
{
	cub3d->cam.p_x = cub3d->config->player_x;
	cub3d->cam.p_y = cub3d->config->player_y;
	if (cub3d->config->orientation == 'N')
		cub3d->cam.pa = 0;
	else if (cub3d->config->orientation == 'S')
		cub3d->cam.pa = M_PI;
	else if (cub3d->config->orientation == 'E')
		cub3d->cam.pa = 2 * M_PI - M_PI / 2;
	else if (cub3d->config->orientation == 'W')
		cub3d->cam.pa = M_PI / 2;
	cub3d->cam.pd_x = cos(cub3d->cam.pa) * 5;
	cub3d->cam.pd_y = sin(cub3d->cam.pa) * 5;
	cub3d->cam.fov = 60;
}


int	main(int argc, char **argv)
{
	t_cub3d			cub3d;

	if (argc != 2)
		return (1);
	cub3d.config = ft_configuration(argv[1]);
	if (!cub3d.config)
		return (1);
	init_cam_settings(&cub3d);
	cub3d.mlx = mlx_init();
	cub3d.win = mlx_new_window(cub3d.mlx, SCREEN_WIDTH + 5, SCREEN_HEIGTH + 5, "Cub3D");
	cub3d.img.mlx = mlx_new_image(cub3d.mlx, SCREEN_WIDTH, SCREEN_HEIGTH);
	cub3d.img.addr = mlx_get_data_addr(cub3d.img.mlx, &cub3d.img.bpp, &cub3d.img.line_len, &cub3d.img.endian);
	mlx_loop_hook(cub3d.mlx, &ft_render_game, &cub3d);
	mlx_hook(cub3d.win, ON_DESTROY, ON_DESTROY, end_program, &cub3d);
	mlx_hook(cub3d.win, 2, 1L << 0, deal_key, &cub3d);
	mlx_loop(cub3d.mlx);
	return (0);
}