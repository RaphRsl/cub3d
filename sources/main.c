/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:12:55 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/11 15:40:34 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_cam_settings(t_cub3d *cub3d)
{
	double	fov_rad;

	cub3d->cam.p_x = cub3d->config->player_x + 0.5;
	cub3d->cam.p_y = cub3d->config->player_y + 0.5;
	cub3d->cam.fov = M_PI / 4;
	if (cub3d->config->orientation == 'E')
		cub3d->cam.pa = 0;
	else if (cub3d->config->orientation == 'W')
		cub3d->cam.pa = M_PI;
	else if (cub3d->config->orientation == 'N')
		cub3d->cam.pa = 2 * M_PI - M_PI / 2;
	else if (cub3d->config->orientation == 'S')
		cub3d->cam.pa = M_PI / 2;
	fov_rad = cub3d->cam.fov * (M_PI / 180.0);
	cub3d->cam.plane_x = cos(fov_rad / 2);
	cub3d->cam.plane_y = sin(fov_rad / 2);
	cub3d->cam.pd_x = cos(cub3d->cam.pa) * 5;
	cub3d->cam.pd_y = sin(cub3d->cam.pa) * 5;	
	cub3d->cam.move_speed = 0.05;
	cub3d->cam.rot_speed = 0.05;
	cub3d->cam.x_mouse = 0;
}

int	main(int argc, char **argv)
{
	t_cub3d			cub3d;

	if (argc != 2)
		return (1);
	init_cub3d(&cub3d);
	cub3d.config = ft_configuration(argv[1]);
	if (!cub3d.config)
		return (end_program(&cub3d));
	init_cam_settings(&cub3d);
	if (!init_mlx_settings(&cub3d))
		return (end_program(&cub3d));
	if (!init_textures(&cub3d))
		return (end_program(&cub3d));
	mlx_loop_hook(cub3d.mlx, &ft_render_game, &cub3d);
	mlx_hook(cub3d.win, ON_DESTROY, ON_DESTROY, end_program, &cub3d);
	mlx_hook(cub3d.win, KEYPRESS, 1L << 0, deal_key, &cub3d);
	mlx_hook(cub3d.win, MOTIONNOTIFY, 1L << 6, deal_mouse, &cub3d);
	mlx_loop(cub3d.mlx);
	return (0);
}
