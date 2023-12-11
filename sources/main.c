/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:12:55 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/11 15:08:13 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_cam_settings(t_cub3d *cub3d)
{
    cub3d->cam.p_x = cub3d->config->player_x + 0.5; // position vector of the player
    cub3d->cam.p_y = cub3d->config->player_y + 0.5;
	//M_PI / 3.0 = 60 degres ; M_PI / 4.0 = 45 degres ; M_PI / 6.0 = 30 degres
	cub3d->cam.fov = M_PI / 4; // Field of view (FOV) is the angle between the left and right sides of your game window (measured in degrees). A larger FOV means that the player will see more on the screen, but the game will appear more distorted. A smaller FOV means that the player will see less, but the game will appear closer to real life.
    if (cub3d->config->orientation == 'E')
        cub3d->cam.pa = 0;	//camera direction vector = 0 rad = 0 degres (East)
    else if (cub3d->config->orientation == 'W')
        cub3d->cam.pa = M_PI; //camera direction vector = 1rad = 180 degres (West)
    else if (cub3d->config->orientation == 'N')
        cub3d->cam.pa = 2 * M_PI - M_PI / 2; //camera direction vector = 1.5 rad = 270 degres (North)
    else if (cub3d->config->orientation == 'S')
        cub3d->cam.pa = M_PI / 2; //camera direction vector = 0.5 rad = 90 degres (South)
    double fov_rad = cub3d->cam.fov * (M_PI / 180.0); // Convert FOV to radians : multiplies the FOV value by π/180 to convert degrees to radians.
    cub3d->cam.plane_x = cos(fov_rad / 2); //Calculates the x-component of the camera's 2D plane based on half of the FOV angle in radians. It uses trigonometric functions (cosine) to determine the x-component of the camera's plane.
    cub3d->cam.plane_y = sin(fov_rad / 2); //Calculates the y-component of the camera's 2D plane based on half of the FOV angle in radians. It uses trigonometric functions (sine) to determine the y-component of the camera's plane.

    cub3d->cam.pd_x = cos(cub3d->cam.pa) * 5; //Calculates the x-component of the camera's direction vector based on the initial angle cub3d->cam.pa. It uses trigonometric functions (cosine) to determine the x-component of the camera's direction and then multiplies it by 5.
    cub3d->cam.pd_y = sin(cub3d->cam.pa) * 5;

	cub3d->cam.move_speed = 0.05;
	cub3d->cam.rot_speed = 0.05;
	cub3d->cam.x_mouse = 0;
}
//proposition de rroussel
// void init_cam_settings(t_cub3d *cub3d)
//{
//     cub3d->cam.p_x = cub3d->config->player_x + 0.5;
//     cub3d->cam.p_y = cub3d->config->player_y + 0.5;
//     cub3d->cam.fov = M_PI / 6;

//     // Initialize camera direction based on orientation
//     if (cub3d->config->orientation == 'E')
//         cub3d->cam.pa = 0;
//     else if (cub3d->config->orientation == 'W')
//         cub3d->cam.pa = M_PI;
//     else if (cub3d->config->orientation == 'N')
//         cub3d->cam.pa = 2 * M_PI - M_PI / 2;
//     else if (cub3d->config->orientation == 'S')
//         cub3d->cam.pa = M_PI / 2;

//     double fov_rad = cub3d->cam.fov * (M_PI / 180.0);
//     cub3d->cam.plane_x = cos(fov_rad / 2);
//     cub3d->cam.plane_y = sin(fov_rad / 2);

//     cub3d->cam.pd_x = cos(cub3d->cam.pa) * 5;
//     cub3d->cam.pd_y = sin(cub3d->cam.pa) * 5;

//     cub3d->cam.move_speed = 0.05;
//     cub3d->cam.rot_speed = 0.05;
// }
//end of proposition de rroussel

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
