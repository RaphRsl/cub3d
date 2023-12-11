/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:28:37 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/11 16:08:25 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_wall(float x, float y, t_cub3d *cub3d)
{
	if (cub3d->config->map[(int)y][(int)x] == 1)
		return (1);
	return (0);
}

void	rotate_left(t_camera *cam, float rot_speed)
{
	double	old_pd_x;
	double	old_plane_x;

	old_pd_x = cam->pd_x;
	old_plane_x = cam->plane_x;
	cam->pd_x = cam->pd_x * cos(-rot_speed) - cam->pd_y
		* sin(-rot_speed);
	cam->pd_y = old_pd_x * sin(-rot_speed) + cam->pd_y
		* cos(-rot_speed);
	cam->plane_x = cam->plane_x * cos(-rot_speed) - cam->plane_y
		* sin(-rot_speed);
	cam->plane_y = old_plane_x * sin(-rot_speed) + cam->plane_y
		* cos(-rot_speed);
	cam->pa -= rot_speed;
	if (cam->pa < 0)
		cam->pa += 2 * M_PI;
}

void	rotate_right(t_camera *cam, float rot_speed)
{
	double	old_pd_x;
	double	old_plane_x;

	old_pd_x = cam->pd_x;
	old_plane_x = cam->plane_x;
	cam->pd_x = cam->pd_x * cos(rot_speed) - cam->pd_y
		* sin(rot_speed);
	cam->pd_y = old_pd_x * sin(rot_speed) + cam->pd_y
		* cos(rot_speed);
	cam->plane_x = cam->plane_x * cos(rot_speed) - cam->plane_y
		* sin(rot_speed);
	cam->plane_y = old_plane_x * sin(rot_speed) + cam->plane_y
		* cos(rot_speed);
	cam->pa += rot_speed;
	if (cam->pa > 2 * M_PI)
		cam->pa -= 2 * M_PI;
}
